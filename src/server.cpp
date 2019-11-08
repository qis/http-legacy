#include <http/chrono.hpp>
#include <http/detail/parse.hpp>
#include <http/mime.hpp>
#include <http/parser.hpp>
#include <http/server.hpp>
#include <ice/log.hpp>
#include <sql/exception.hpp>
#include <zlib/stream.hpp>
#include <sys/mman.h>
#include <sys/stat.h>
#include <array>
#include <exception>
#include <mutex>
#include <net>
#include <sstream>
#include <thread>
#include <vector>
#include <cstdio>

#ifdef _MSC_VER
#include <fcntl.h>
#include <io.h>
#define S_ISREG(m) (((m)&S_IFMT) == S_IFREG)
#define S_ISDIR(m) (((m)&S_IFMT) == S_IFDIR)
#endif

namespace http {
namespace {

// TODO: Rewrite it to check for input correctness.
inline std::string decode(const char* src, std::size_t size) {
  std::string dst;
  dst.reserve(size);
  for (std::size_t i = 0; i < size; i++) {
    if (int(src[i]) == '%' && i + 2 < size) {
      int number = 0;
      std::array<char, 3> buffer = { { src[i + 1], src[i + 2], '\0' } };
      if (std::sscanf(buffer.data(), "%x", &number) == 1) {
        auto c = static_cast<char>(number);
        dst.push_back(c);
        i = i + 2;
        continue;
      }
    }
    dst.push_back(src[i]);
  }
  return dst;
}

inline std::string decode(const std::string& str) {
  return decode(str.data(), str.size());
}

inline std::string compress(const char* data, std::size_t size, zlib::format format) {
  std::string buffer;
  buffer.reserve(size);
  zlib::deflate_stream stream(format);
  stream.process(
    data, size, [&buffer](const char* data, std::size_t size) { buffer.append(data, size); }, true);
  buffer.shrink_to_fit();
  return buffer;
}

struct file {
  int handle = -1;

  file() = default;

  explicit file(const std::filesystem::path& path, int mode) {
    handle = ::open(reinterpret_cast<const char*>(path.u8string().data()), mode);
  }

  file(file&& other) {
    std::swap(other.handle, handle);
  }

  file& operator=(file&& other) {
    std::swap(other.handle, handle);
    return *this;
  }

  ~file() {
    if (handle != -1) {
      ::close(handle);
    }
  }

  operator bool() const {
    return handle != -1;
  }
};

struct memory {
  void* addr = MAP_FAILED;
  size_t size = 0;

  memory() = default;

  explicit memory(int file, size_t size) : size(size) {
    addr = ::mmap(nullptr, size, PROT_READ, MAP_SHARED, file, 0);
  }

  memory(memory&& other) {
    std::swap(other.addr, addr);
    std::swap(other.size, size);
  }

  memory& operator=(memory&& other) {
    std::swap(other.addr, addr);
    std::swap(other.size, size);
    return *this;
  }

  ~memory() {
    if (addr != MAP_FAILED) {
      ::munmap(addr, size);
    }
  }

  operator bool() const {
    return addr != MAP_FAILED;
  }
};

class connection : public http::parser<connection, HTTP_REQUEST>, public std::enable_shared_from_this<connection> {
public:
  connection(server& server, std::net::io_context& io_context, std::net::ip::tcp::socket socket, std::size_t root = 0)
    : server_(server), io_context_(io_context), socket_(std::move(socket)), root_(root), inflate_stream_(zlib::format::deflate) {
    try {
      endpoint_ = socket_.remote_endpoint().address().to_string();
    }
    catch (...) {
      endpoint_.clear();
    }
  }

  connection(connection&& other) = delete;
  connection(const connection& other) = delete;

  connection& operator=(connection&& other) = delete;
  connection& operator=(const connection& other) = delete;

  void start() {
    read(shared_from_this());
  }

  void close() {
    std::error_code ec;
    socket_.close(ec);
  }

  int on_message_begin() {
    header_ = header::none;
    path_.clear();
    name_.clear();
    name_parsed_ = false;
    inflate_stream_.reset();
    inflate_ = false;
    request_.client = endpoint_;
    request_.server = server_.endpoint();
    return 0;
  }

  int on_url(std::string_view data) {
    path_.append(data);
    return 0;
  }

  int on_status(std::string_view data) {
    return 0;
  }

  int on_header_field(std::string_view data) {
    if (name_parsed_) {
      name_.clear();
      name_parsed_ = false;
    }
    name_.append(data);
    return 0;
  }

  int on_header_value(std::string_view data) {
    if (!name_parsed_) {
      name_parsed_ = true;
      header_ = detail::parse_header(name_);
      auto it = request_.headers.find(header_);
      if (it != request_.headers.end()) {
        it->second.append(", ");
      }
    }
    if (header_ != header::none) {
      request_.headers[header_].append(data);
    }
    return 0;
  }

  int on_headers_complete(short major, short minor) {
    request_.method = static_cast<http::method>(method);
    if (request_.method == method::none) {
      errc(HPE_INVALID_METHOD);
      return 2;  // error
    }

    request_.version = version(static_cast<std::uint8_t>(major), static_cast<std::uint8_t>(minor));
    if (request_.version != version(1, 0) && request_.version != version(1, 1)) {
      errc(HPE_INVALID_VERSION);
      return 2;  // error
    }

    http_parser_url url = {};
    http_parser_url_init(&url);
    if (http_parser_parse_url(path_.data(), path_.size(), 0, &url)) {
      errc(HPE_INVALID_URL);
      return 2;  // error
    }

    // Path
    {
      auto off = url.field_data[UF_PATH].off;
      auto len = url.field_data[UF_PATH].len;
      if (off >= 0 && len > 0) {
        std::string str(path_.data() + off, len);
        if (!str.empty() && str.back() == '/') {
          request_.directory = true;
        }
        std::uint64_t i = 0;
        std::filesystem::path path;
        std::istringstream iss(str);
        for (std::string e; std::getline(iss, e, '/');) {
          if (e == "..") {
            path = path.parent_path();
            i--;
          } else if (!e.empty() && e != "." && ++i > static_cast<std::uint64_t>(root_)) {
            e = decode(e);
            if (e == ".." || std::find_if(e.begin(), e.end(), [](auto c) { return c == '/' || c == '\\'; }) != e.end()) {
              errc(HPE_INVALID_PATH);
              return 2;  // error
            }
            path /= std::filesystem::u8path(e);
          }
        }
        request_.path = '/' + std::string(reinterpret_cast<const char*>(path.generic_u8string().data()));
      } else {
        errc(HPE_INVALID_PATH);
        return 2;  // error
      }
    }

    // Query
    {
      auto off = url.field_data[UF_QUERY].off;
      auto len = url.field_data[UF_QUERY].len;
      if (off >= 0 && len > 0) {
        request_.query = decode(path_.data() + off, len);
      }
    }

    // Headers
    for (auto& header : request_.headers) {
      header.second = decode(header.second);
    }

    // Client
    {
      auto it = request_.headers.find(header::x_client);
      if (it != request_.headers.end()) {
        endpoint_ = request_.client = it->second;
      }
    }

    // Server
    {
      auto it = request_.headers.find(header::x_server);
      if (it != request_.headers.end()) {
        request_.server = it->second;
      }
    }

    // Content Encoding
    {
      auto it = request_.headers.find(header::content_encoding);
      if (it != request_.headers.end()) {
        if (it->second.find("deflate") != std::string::npos) {
          inflate_ = true;
        }
      }
    }

    // Transfer Encoding
    {
      auto it = request_.headers.find(header::transfer_encoding);
      if (it != request_.headers.end()) {
        if (it->second.find("chunked") != std::string::npos) {
          return 0;
        }
      }
    }

    // Session ID
    {
      auto it = request_.headers.find(header::cookie);
      if (it != request_.headers.end()) {
        auto pos = it->second.find("session=");
        if (pos != std::string::npos && it->second.size() - pos >= 36 + 8) {
          auto str = std::string_view(it->second.data() + pos + 8, 36);
          if (ice::uuid::check(str)) {
            request_.session = ice::uuid(str);
          }
        }
      }
    }

    // Body Size
    {
      auto it = request_.headers.find(header::content_length);
      if (it != request_.headers.end()) {
        if (auto size = static_cast<std::size_t>(std::stoull(it->second))) {
          request_.body.reserve(inflate_ ? static_cast<std::size_t>(size * 1.5) : size);
        }
        return 0;
      }
    }
    return 1;
  }

  int on_body(std::string_view data) {
    if (inflate_) {
      inflate_stream_.process(data.data(), data.size(), [this](const char* data, std::size_t size) {
        request_.body.append(data, size);
      });
    } else {
      request_.body.append(data);
    }
    return 0;
  }

  int on_message_complete() {
    if (inflate_) {
      inflate_stream_.finish([this](const char* data, std::size_t size) { request_.body.append(data, size); });
    }
    request_.body.shrink_to_fit();
    auto it = request_.headers.find(header::connection);
    if (request_.version <= version(1, 0)) {
      if (it == request_.headers.end() || it->second.find("keep-alive") == std::string::npos) {
        close_ = true;
      }
    } else {
      if (it != request_.headers.end() && it->second.find("close") != std::string::npos) {
        close_ = true;
      }
    }
    handle(errc(), std::move(request_));
    errc(HPE_OK);
    return 0;
  }

  int on_chunk_header() {
    return 0;
  }

  int on_chunk_complete() {
    return 0;
  }

private:
  void read(std::shared_ptr<connection> self) {
    socket_.async_read_some(std::net::buffer(buffer_), [this, self(std::move(self))](std::error_code ec, std::size_t size) {
      if (ec) {
        if (ec != std::net::error::eof && ec != std::net::error::operation_aborted) {
          ice::log::error() << endpoint_ << ": read error: " << ec;
        }
        return;
      }
#ifdef __OPTIMIZE__
      try {
#endif
        auto data = buffer_.data();
        while (!close_ && size > 0) {
          auto read = execute(data, size);
          if (errc() != errc::HPE_OK) {
            handle(errc(), std::move(request_));
            return;
          }
          data += read;
          size -= read;
        }
#ifdef __OPTIMIZE__
      }
      catch (...) {
        ice::log::critical() << endpoint_ << ": parse error: " << std::current_exception();
        return;
      }
#endif
      if (!close_) {
        read(std::move(self));
      }
    });
  }

  void handle(std::error_code ec, request request) {
    auto self = shared_from_this();
    std::net::post(io_context_, [this, self, ec, request(std::move(request))]() mutable {
      if (ec) {
        if (ec == HPE_INVALID_METHOD) {
          write(request, response(405));
          return;
        }
        if (ec == HPE_INVALID_VERSION) {
          write(request, response(505));
          return;
        }
        if (ec == HPE_INVALID_CONSTANT) {
          write(request, response(400));
          return;
        }
        write(request, response(400, ec.message()));
        return;
      }
      if (server_.debug()) {
        write(request, server_.handle(request));
      } else {
        try {
          write(request, server_.handle(request));
        }
        catch (const error& e) {
          ice::json data;
          data["what"] = e.what();
          if (const auto info = e.info()) {
            data["info"] = info;
          }
          write(request, response(e) << std::move(data));
        }
        catch (const ice::exception& e) {
          ice::json data;
          data["what"] = e.what();
          if (const auto info = e.info()) {
            data["info"] = info;
          }
          write(request, response(500) << std::move(data));
        }
        catch (const sql::exception& e) {
          const auto what = std::string(e.what());
          ice::json data;
          data["what"] = what;
          if (server_.query()) {
            data["info"] = std::string(e.query());
          }
          write(request, response(what == "step error: constraint failed" ? 409 : 400) << std::move(data));
        }
        catch (const std::domain_error& e) {
          ice::json data;
          data["what"] = e.what();
          write(request, response(400) << std::move(data));
        }
        catch (const std::exception& e) {
          ice::json data;
          data["what"] = e.what();
          write(request, response(500) << std::move(data));
        }
        catch (...) {
          write(request, response(500));
        }
      }
    });
  }

  void write(const request& request, response response) {
    std::optional<zlib::format> encoding;
    {
      auto it = request.headers.find(header::accept_encoding);
      if (it != request.headers.end()) {
        if (it->second.find("deflate") != std::string::npos) {
          encoding = zlib::format::deflate;
        } else if (it->second.find("gzip") != std::string::npos) {
          encoding = zlib::format::gzip;
        }
      }
    }

    // Empty response body.
    if (response.data.index() == 0) {
      write(request, response.status, response.headers);
      return;
    }

    // JSON response body.
    if (response.data.index() == 2) {
      response.data = std::get<ice::json>(response.data).dump();
      response.headers[header::content_type] = "application/json";
    }

    // Data response body.
    if (response.data.index() == 1) {
      auto& data = std::get<std::string>(response.data);
      if (encoding && data.size() > 1024) {
        response.headers[header::content_encoding] = encoding.value() == zlib::format::deflate ? "deflate" : "gzip";
        data = compress(data.data(), data.size(), encoding.value());
      }
      write(request, response.status, response.headers, std::move(data));
      return;
    }

    // File response body.
    auto path = std::get<http::path>(response.data);

    if (std::filesystem::is_directory(path.filename)) {
      path.filename /= "index.html";
    }

    file file(path.filename, O_RDONLY);
    if (!file) {
      write(request, status(404), response.headers);
      return;
    }

    struct stat sb = {};
    if (fstat(file.handle, &sb) == -1) {
      write(request, status(404), response.headers);
      return;
    }

    if (!S_ISREG(sb.st_mode)) {
      write(request, status(403), response.headers);
      return;
    }

    if (sb.st_size == 0) {
      response.headers[header::content_type] = http::mime(path.filename);
      write(request, status(200), response.headers);
      return;
    }

#ifdef _MSC_VER
    auto modified = clock::from_time_t(sb.st_mtime);
#else
    auto modified = clock::from_time_t(sb.st_mtim.tv_sec);
#endif
    {
      auto it = request.headers.find(header::if_modified_since);
      if (it != request.headers.end()) {
        if (modified <= http::parse(it->second)) {
          write(request, status(304), response.headers);
          return;
        }
      }
    }

    memory memory(file.handle, sb.st_size);
    if (!memory) {
      write(request, status(403), response.headers);
      return;
    }

    if (path.expires > std::chrono::seconds(0)) {
      response.headers[header::last_modified] = http::format(modified);
    }

    if (path.must_revalidate) {
      response.headers[header::cache_control] = "no-cache, must-revalidate";
    } else {
      response.headers[header::cache_control] = "max-age=" + std::to_string(path.expires.count());
    }

    response.headers[header::content_type] = http::mime(path.filename);

    if (encoding && memory.size > 1024) {
      response.headers[header::content_encoding] = encoding.value() == zlib::format::deflate ? "deflate" : "gzip";
      auto data = compress(reinterpret_cast<const char*>(memory.addr), memory.size, encoding.value());
      write(request, response.status, response.headers, std::move(data));
      return;
    }

    write(request, response.status, response.headers, std::move(memory));
  }

  void write(const request& request, const status& status, headers& headers) {
    info(request, status);
    headers[header::content_length] = "0";
    auto store = std::make_shared<std::string>(format(request.version, status, headers));
    auto buffer = std::net::buffer(*store);
    std::net::async_write(socket_, buffer, [this, self = shared_from_this(), store](std::error_code ec, std::size_t) {
      if (ec) {
        ice::log::error() << endpoint_ << ": write error: " << ec;
        close();
      }
    });
  }

  void write(const request& request, const status& status, headers& headers, std::string body) {
    info(request, status, body.data());
    if (status.code < 500) {
      headers[header::content_length] = std::to_string(body.size());
      auto store = std::make_shared<std::pair<std::string, std::string>>(format(request.version, status, headers), std::move(body));
      std::array<std::net::const_buffer, 2> buffer = { {
        std::net::buffer(store->first),
        std::net::buffer(store->second),
      } };
      std::net::async_write(socket_, buffer, [this, self = shared_from_this(), store](std::error_code ec, std::size_t) {
        if (ec) {
          ice::log::error() << endpoint_ << ": write error: " << ec;
          close();
        }
      });
    } else {
      headers[header::content_length] = "0";
      auto store = std::make_shared<std::string>(format(request.version, status, headers));
      auto buffer = std::net::buffer(*store);
      std::net::async_write(socket_, buffer, [this, self = shared_from_this(), store](std::error_code ec, std::size_t) {
        if (ec) {
          ice::log::error() << endpoint_ << ": write error: " << ec;
          close();
        }
      });
    }
  }

  void write(const request& request, const status& status, headers& headers, memory memory) {
    info(request, status);
    headers[header::content_length] = std::to_string(memory.size);
    auto store = std::make_shared<std::string>(format(request.version, status, headers));
    std::array<std::net::const_buffer, 2> buffer = { {
      std::net::buffer(*store),
      std::net::buffer(memory.addr, memory.size),
    } };
    std::net::async_write(socket_, buffer, [this, self = shared_from_this(), store, memory(std::move(memory))](std::error_code ec, std::size_t) {
      if (ec) {
        ice::log::error() << endpoint_ << ": write error: " << ec;
        close();
      }
    });
  }

  void info(const request& request, const status& status, const char* data = nullptr) {
    auto severity = ice::log::severity::info;
    if (status.code >= 500) {
      severity = ice::log::severity::error;
    } else if (status.code >= 400) {
      severity = ice::log::severity::warning;
    } else if (status.code == 304 || request.path.compare(0, 5, "/rest") != 0 || request.path.find("keepalive") != std::string::npos) {
      severity = ice::log::severity::debug;
    }
    {
      ice::log::stream os(severity);
      os << endpoint_ << ": " << status.code << ' ' << request.method << ' ' << request.path;
      if (request.query) {
        os << '?' << request.query.value();
      }
      if (status.text) {
        os << " (" << status.text.value() << ')';
      }
    }
    if (data && status.code >= 400) {
      ice::log::debug() << endpoint_ << ": " << status.code << ' ' << request.method << ' ' << data;
    }
  }

  std::string format(version version, const status& status, const headers& headers) {
    std::ostringstream oss;
    oss << version << ' ' << status << "\r\n";
    for (const auto& header : headers) {
      oss << header.first << ": " << header.second << "\r\n";
    }
    oss << "\r\n";
    return oss.str();
  }

  http::server& server_;
  std::net::io_context& io_context_;
  std::net::ip::tcp::socket socket_;
  std::string endpoint_;
  std::array<char, 8192> buffer_;

  http::request request_ = {};
  http::header header_ = http::header::none;

  std::string path_;
  std::string name_;
  std::size_t root_ = 0;
  bool name_parsed_ = false;

  zlib::inflate_stream inflate_stream_;
  bool inflate_ = false;

  bool close_ = false;
};

}  // namespace

class server::impl {
public:
  using system_timer = std::net::basic_waitable_timer<std::chrono::system_clock>;

  impl(server& server, const std::string& address, const std::string& service, bool reuse_address, std::size_t root)
    : server_(server), io_context_(), acceptor_(io_context_), root_(root) {
    std::net::ip::tcp::resolver resolver(io_context_);
    const auto it = resolver.resolve(std::string(address), std::string(service), std::net::ip::resolver_base::flags::numeric_host);
    const auto endpoint = it.begin()->endpoint();
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(std::net::ip::tcp::acceptor::reuse_address(reuse_address));
    acceptor_.bind(endpoint);
    acceptor_.listen();
    std::ostringstream oss;
    oss << endpoint;
    endpoint_ = oss.str();
    accept();
  }

  std::string endpoint() const {
    return endpoint_;
  }

  void run(std::size_t threads) {
    if (threads > 1) {
      ice::log::info() << endpoint() << " on " << threads << " threads";
    } else {
      ice::log::info() << endpoint();
    }

    std::mutex mutex;
    std::exception_ptr exception;
    std::vector<std::thread> thread_pool;
    for (std::size_t i = 1; i < threads; i++) {
      thread_pool.emplace_back([&]() {
        try {
          io_context_.run();
        }
        catch (...) {
          std::lock_guard lock(mutex);
          exception = std::current_exception();
          stop();
        }
      });
    }

    io_context_.run();

    for (auto& thread : thread_pool) {
      if (thread.joinable()) {
        thread.join();
      }
    }
    if (exception) {
      std::rethrow_exception(exception);
    }
  }

  void stop() {
    io_context_.stop();
  }

  template <typename T>
  void queue(std::string name, T expiry_time, std::function<void()> handler) {
    std::lock_guard<std::recursive_mutex> lock(timers_mutex_);
    abort(name);
    auto it = timers_.emplace(
      std::make_pair<std::string, system_timer>(std::string(name), system_timer(io_context_, expiry_time)));
    it.first->second.async_wait([this, name, handler = std::move(handler)](std::error_code ec) {
      std::lock_guard<std::recursive_mutex> lock(timers_mutex_);
      timers_.erase(name);
      if (!ec) {
        try {
          handler();
        }
        catch (const std::exception& e) {
          ice::log::error() << name << ": " << e.what();
        }
        catch (...) {
          ice::log::error() << name << " error";
        }
      }
    });
  }

  void abort(std::string name) {
    std::unique_ptr<system_timer> timer;
    {
      std::lock_guard<std::recursive_mutex> lock(timers_mutex_);
      auto it = timers_.find(name);
      if (it != timers_.end()) {
        timer = std::make_unique<system_timer>(std::move(it->second));
      }
    }
    if (timer) {
      timer->cancel();
    }
  }

private:
  void accept() {
    acceptor_.async_accept([this](std::error_code ec, std::net::ip::tcp::socket socket) {
      if (ec) {
        if (!acceptor_.is_open()) {
          return;
        }
        if (ec != std::net::error::operation_aborted) {
          ice::log::debug() << socket.remote_endpoint() << ": " << ec;
        }
      } else {
        std::make_shared<connection>(server_, io_context_, std::move(socket), root_)->start();
      }
      accept();
    });
  }

  server& server_;
  std::net::io_context io_context_;
  std::net::ip::tcp::acceptor acceptor_;
  std::map<std::string, system_timer> timers_;
  std::recursive_mutex timers_mutex_;
  std::string endpoint_;
  std::size_t root_ = 0;
};

server::server(const std::string& address, const std::string& service, bool reuse_address, std::size_t root)
  : impl_(std::make_unique<impl>(*this, address, service, reuse_address, root)) {}

server::~server() {}

void server::queue(std::string name, std::chrono::system_clock::time_point expiry_time, std::function<void()> handler) {
  impl_->queue(std::move(name), std::move(expiry_time), std::move(handler));
}

void server::queue(std::string name, std::chrono::milliseconds expiry_time, std::function<void()> handler) {
  impl_->queue(std::move(name), std::move(expiry_time), std::move(handler));
}

void server::abort(std::string name) {
  impl_->abort(std::move(name));
}

std::string server::endpoint() const {
  return impl_->endpoint();
}

void server::run(std::size_t threads) {
  impl_->run(threads);
}

void server::stop() {
  impl_->stop();
}

}  // namespace http
