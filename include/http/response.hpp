#pragma once
#include <http/types.hpp>

namespace http {

class response {
public:
  response(int code) : status(code) {}
  response(int code, std::string status) : status(code, std::move(status)) {}
  explicit response(http::status status) : status(std::move(status)) {}

  http::status status;
  http::headers headers;
  http::data data;

  template <typename T>
  response& operator<<(T&& value) {
    data.emplace<ice::json>(std::forward<T>(value));
    return *this;
  }

  template <typename T>
  response& operator<<(std::optional<T> opt) {
    if (opt) {
      *this << std::move(opt.value());
    } else {
      status = http::status(404);
      data = nullptr;
    }
    return *this;
  }

  response& operator<<(std::nullptr_t) {
    data.emplace<std::nullptr_t>(nullptr);
    return *this;
  }

  template <std::size_t N>
  response& operator<<(const char* (&STR)[N]) {
    data.emplace<std::string>(STR);
    return *this;
  }

  response& operator<<(const char* str) {
    data.emplace<std::string>(str);
    return *this;
  }

  response& operator<<(std::string str) {
    data.emplace<std::string>(std::move(str));
    return *this;
  }

  response& operator<<(path path) {
    data.emplace<http::path>(std::move(path));
    return *this;
  }

  void clear() {
    status = {};
    headers.clear();
    data = nullptr;
  }
};

}  // namespace http
