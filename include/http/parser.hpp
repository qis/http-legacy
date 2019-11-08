#pragma once
#include <http_parser.h>
#include <string>
#include <system_error>
#include <type_traits>

namespace http {

using errc = http_errno;

template <typename I, http_parser_type Type = HTTP_BOTH>
class parser : public http_parser {
public:
  //
  // Define one or more of the following functions in the derived class.
  //
  // int on_url(std::string_view data);
  // int on_status(std::string_view data);
  // int on_header_field(std::string_view data);
  // int on_header_value(std::string_view data);
  // int on_headers_complete(short major, short minor);
  // int on_body(std::string_view data);
  // int on_message_complete();
  // int on_chunk_header();
  //

  parser() noexcept {
    http_parser_init(this, Type);
    if constexpr (std::is_same_v<decltype(&I::on_message_begin), int (I::*)()>) {
      settings_.on_message_begin = on_message_begin;
    }
    if constexpr (std::is_same_v<decltype(&I::on_url), int (I::*)(std::string_view)>) {
      settings_.on_url = on_url;
    }
    if constexpr (std::is_same_v<decltype(&I::on_status), int (I::*)(std::string_view)> && (Type == HTTP_RESPONSE || Type == HTTP_BOTH)) {
      settings_.on_status = on_status;
    }
    if constexpr (std::is_same_v<decltype(&I::on_header_field), int (I::*)(std::string_view)>) {
      settings_.on_header_field = on_header_field;
    }
    if constexpr (std::is_same_v<decltype(&I::on_header_value), int (I::*)(std::string_view)>) {
      settings_.on_header_value = on_header_value;
    }
    if constexpr (std::is_same_v<decltype(&I::on_headers_complete), int (I::*)(short, short)>) {
      settings_.on_headers_complete = on_headers_complete;
    }
    if constexpr (std::is_same_v<decltype(&I::on_body), int (I::*)(std::string_view)>) {
      settings_.on_body = on_body;
    }
    if constexpr (std::is_same_v<decltype(&I::on_message_complete), int (I::*)()>) {
      settings_.on_message_complete = on_message_complete;
    }
    if constexpr (std::is_same_v<decltype(&I::on_chunk_header), int (I::*)()>) {
      settings_.on_chunk_header = on_chunk_header;
    }
    if constexpr (std::is_same_v<decltype(&I::on_chunk_complete), int (I::*)()>) {
      settings_.on_chunk_complete = on_chunk_complete;
    }
  }

  parser(const parser& other) = delete;
  parser& operator=(const parser& other) = delete;

  http::errc errc() const {
    return static_cast<http::errc>(http_errno);
  }

  void errc(http::errc ev) {
    http_errno = static_cast<decltype(http_errno)>(ev);
  }

  std::size_t execute(const char* data, std::size_t size) {
    return http_parser_execute(this, &settings_, data, size);
  }

private:
  static int on_message_begin(http_parser* parser) {
    return static_cast<I*>(parser)->on_message_begin();
  }

  static int on_url(http_parser* parser, const char* data, size_t size) {
    return static_cast<I*>(parser)->on_url(std::string_view(data, size));
  }

  static int on_status(http_parser* parser, const char* data, size_t size) {
    return static_cast<I*>(parser)->on_status(std::string_view(data, size));
  }

  static int on_header_field(http_parser* parser, const char* data, size_t size) {
    return static_cast<I*>(parser)->on_header_field(std::string_view(data, size));
  }

  static int on_header_value(http_parser* parser, const char* data, size_t size) {
    return static_cast<I*>(parser)->on_header_value(std::string_view(data, size));
  }

  static int on_headers_complete(http_parser* parser) {
    return static_cast<I*>(parser)->on_headers_complete(parser->http_major, parser->http_minor);
  }

  static int on_body(http_parser* parser, const char* data, size_t size) {
    return static_cast<I*>(parser)->on_body(std::string_view(data, size));
  }

  static int on_message_complete(http_parser* parser) {
    return static_cast<I*>(parser)->on_message_complete();
  }

  static int on_chunk_header(http_parser* parser) {
    return static_cast<I*>(parser)->on_chunk_header();
  }

  static int on_chunk_complete(http_parser* parser) {
    return static_cast<I*>(parser)->on_chunk_complete();
  }

  http_parser_settings settings_ = {};
};

class error_category_impl : public std::error_category {
public:
  const char* name() const noexcept override {
    return "http";
  }

  std::string message(int ev) const override {
    if (auto str = http_errno_name(static_cast<http_errno>(ev))) {
      return str;
    }
    return std::to_string(ev);
  }
};

inline const std::error_category& error_category() {
  static const error_category_impl error_category;
  return error_category;
}

inline std::error_code make_error_code(http::errc ev) noexcept {
  return std::error_code(static_cast<int>(ev), http::error_category());
}

}  // namespace http

inline std::error_code make_error_code(http_errno ev) noexcept {
  return std::error_code(static_cast<int>(ev), http::error_category());
}

namespace std {

template <>
struct is_error_code_enum<http_errno> : true_type {};

}  // namespace std
