#include <http/types.hpp>
#include <iomanip>

namespace http {

std::ostream& operator<<(std::ostream& os, method m) {
  switch (m) {
  case method::del:
    return os << "[DELETE]";
  case method::get:
    return os << "[GET   ]";
  case method::head:
    return os << "[HEAD  ]";
  case method::post:
    return os << "[POST  ]";
  case method::put:
    return os << "[PUT   ]";
  case method::connect:
    return os << "[CONNECT]";
  case method::options:
    return os << "[OPTIONS]";
  case method::trace:
    return os << "[TRACE ]";
  case method::copy:
    return os << "[COPY  ]";
  case method::lock:
    return os << "[LOCK  ]";
  case method::mkcol:
    return os << "[MKCOL ]";
  case method::move:
    return os << "[MOVE  ]";
  case method::propfind:
    return os << "[PROPFIND]";
  case method::proppatch:
    return os << "[PROPPATCH]";
  case method::search:
    return os << "[SEARCH]";
  case method::unlock:
    return os << "[UNLOCK]";
  case method::bind:
    return os << "[BIND  ]";
  case method::rebind:
    return os << "[REBIND]";
  case method::unbind:
    return os << "[UNBIND]";
  case method::acl:
    return os << "[ACL   ]";
  case method::report:
    return os << "[REPORT]";
  case method::mkactivity:
    return os << "[MKACTIVITY]";
  case method::checkout:
    return os << "[CHECKOUT]";
  case method::merge:
    return os << "[MERGE ]";
  case method::msearch:
    return os << "[M-SEARCH]";
  case method::notify:
    return os << "[NOTIFY]";
  case method::subscribe:
    return os << "[SUBSCRIBE]";
  case method::unsubscribe:
    return os << "[UNSUBSCRIBE]";
  case method::patch:
    return os << "[PATCH ]";
  case method::purge:
    return os << "[PURGE ]";
  case method::mkcalendar:
    return os << "[MKCALENDAR]";
  case method::link:
    return os << "[LINK  ]";
  case method::unlink:
    return os << "[UNLINK]";
  case method::none:
    return os << "[NONE  ]";
  }
  return os << static_cast<std::uint8_t>(m);
}

std::ostream& operator<<(std::ostream& os, header h) {
  switch (h) {
  case header::accept_encoding:
    return os << "Accept-Encoding";
  case header::cache_control:
    return os << "Cache-Control";
  case header::connection:
    return os << "Connection";
  case header::content_disposition:
    return os << "Content-Disposition";
  case header::content_encoding:
    return os << "Content-Encoding";
  case header::content_type:
    return os << "Content-Type";
  case header::content_length:
    return os << "Content-Length";
  case header::cookie:
    return os << "Cookie";
  case header::date:
    return os << "Date";
  case header::expect:
    return os << "Expect";
  case header::expires:
    return os << "Expires";
  case header::host:
    return os << "Host";
  case header::if_modified_since:
    return os << "If-Modified-Since";
  case header::last_modified:
    return os << "Last-Modified";
  case header::location:
    return os << "Location";
  case header::origin:
    return os << "Origin";
  case header::pragma:
    return os << "Pragma";
  case header::refresh:
    return os << "Refresh";
  case header::server:
    return os << "Server";
  case header::set_cookie:
    return os << "Set-Cookie";
  case header::transfer_encoding:
    return os << "Transfer-Encoding";
  case header::upgrade:
    return os << "Upgrade";
  case header::user_agent:
    return os << "User-Agent";
  case header::x_client:
    return os << "X-Client";
  case header::x_server:
    return os << "X-Server";
  case header::none:
    return os << "None";
  }
  return os << static_cast<std::uint8_t>(h);
}

const char* status::what() const noexcept {
  if (text) {
    return text.value().c_str();
  }
  switch (code) {
  case 100:
    return "Continue";
  case 101:
    return "Switching Protocols";
  case 102:
    return "Processing";
  case 200:
    return "OK";
  case 201:
    return "Created";
  case 202:
    return "Accepted";
  case 203:
    return "Non-Authoritative Information";
  case 204:
    return "No Content";
  case 205:
    return "Reset Content";
  case 206:
    return "Partial Content";
  case 207:
    return "Multi-Status";
  case 208:
    return "Already Reported";
  case 226:
    return "IM Used";
  case 300:
    return "Multiple Choices";
  case 301:
    return "Moved Permanently";
  case 302:
    return "Found";
  case 303:
    return "See Other";
  case 304:
    return "Not Modified";
  case 305:
    return "Use Proxy";
  case 306:
    return "Switch Proxy";
  case 307:
    return "Temporary Redirect";
  case 308:
    return "Permanent Redirect";
  case 400:
    return "Bad Request";
  case 401:
    return "Unauthorized";
  case 402:
    return "Payment Required";
  case 403:
    return "Forbidden";
  case 404:
    return "Not Found";
  case 405:
    return "Method Not Allowed";
  case 406:
    return "Not Acceptable";
  case 407:
    return "Proxy Authentication Required";
  case 408:
    return "Request Timeout";
  case 409:
    return "Conflict";
  case 410:
    return "Gone";
  case 411:
    return "Length Required";
  case 412:
    return "Precondition Failed";
  case 413:
    return "Payload Too Large";
  case 414:
    return "URI Too Long";
  case 415:
    return "Unsupported Media Type";
  case 416:
    return "Range Not Satisfiable";
  case 417:
    return "Expectation Failed";
  case 418:
    return "I'm a teapot";
  case 421:
    return "Misdirected Request";
  case 422:
    return "Unprocessable Entity";
  case 423:
    return "Locked";
  case 424:
    return "Failed Dependency";
  case 426:
    return "Upgrade Required";
  case 428:
    return "Precondition Required";
  case 429:
    return "Too Many Requests";
  case 431:
    return "Request Header Fields Too Large";
  case 451:
    return "Unavailable For Legal Reasons";
  case 500:
    return "Internal Server Error";
  case 501:
    return "Not Implemented";
  case 502:
    return "Bad Gateway";
  case 503:
    return "Service Unavailable";
  case 504:
    return "Gateway Timeout";
  case 505:
    return "HTTP Version Not Supported";
  case 507:
    return "Insufficient Storage";
  case 508:
    return "Loop Detected";
  case 510:
    return "Not Extended";
  case 511:
    return "Network Authentication Required";
  }
  return "Unknown";
}

std::ostream& operator<<(std::ostream& os, const status& s) {
  return os << s.code << ' ' << s.what();
}

std::ostream& operator<<(std::ostream& os, version v) {
  switch (v.value()) {
  case 0x10:
    return os << "HTTP/1.0";
  case 0x11:
    return os << "HTTP/1.1";
  case 0x20:
    return os << "HTTP/2";
  }
  auto flags = os.flags();
  os << "HTTP/" << std::hex << (v.value() >> 4) << '.' << (v.value() & 0x0F);
  os.flags(flags);
  return os;
}

}  // namespace http
