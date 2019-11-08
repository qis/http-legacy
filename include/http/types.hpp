#pragma once
#include <ice/exception.hpp>
#include <ice/json.hpp>
#include <chrono>
#include <filesystem>
#include <map>
#include <optional>
#include <ostream>
#include <string>
#include <variant>
#include <cstddef>
#include <cstdint>

#ifdef major
#undef major
#endif

#ifdef minor
#undef minor
#endif

namespace http {

using days = std::chrono::duration<int, std::ratio_multiply<std::ratio<24>, std::chrono::hours::period>>;
using weeks = std::chrono::duration<int, std::ratio_multiply<std::ratio<7>, days::period>>;
using years = std::chrono::duration<int, std::ratio_multiply<std::ratio<146097, 400>, days::period>>;
using months = std::chrono::duration<int, std::ratio_divide<years::period, std::ratio<12>>>;

enum class method : std::uint8_t {
  del = 0,
  get = 1,
  head = 2,
  post = 3,
  put = 4,
  connect = 5,
  options = 6,
  trace = 7,
  copy = 8,
  lock = 9,
  mkcol = 10,
  move = 11,
  propfind = 12,
  proppatch = 13,
  search = 14,
  unlock = 15,
  bind = 16,
  rebind = 17,
  unbind = 18,
  acl = 19,
  report = 20,
  mkactivity = 21,
  checkout = 22,
  merge = 23,
  msearch = 24,
  notify = 25,
  subscribe = 26,
  unsubscribe = 27,
  patch = 28,
  purge = 29,
  mkcalendar = 30,
  link = 31,
  unlink = 32,
  none = 99
};

std::ostream& operator<<(std::ostream& os, method m);

using query = std::optional<std::string>;

// https://en.wikipedia.org/wiki/List_of_HTTP_header_fields

enum class header : std::uint8_t {
  accept_encoding,      // Accept-Encoding
  cache_control,        // Cache-Control
  connection,           // Connection
  content_disposition,  // Content-Disposition
  content_encoding,     // Content-Encoding
  content_type,         // Content-Type
  content_length,       // Content-Length
  cookie,               // Cookie
  date,                 // Date
  expect,               // Expect
  expires,              // Expires
  host,                 // Host
  if_modified_since,    // If-Modified-Since
  last_modified,        // Last-Modified
  location,             // Location
  origin,               // Origin
  pragma,               // Pragma
  refresh,              // Refresh
  server,               // Server
  set_cookie,           // Set-Cookie
  transfer_encoding,    // Transfer-Encoding
  upgrade,              // Upgrade
  user_agent,           // User-Agent
  x_client,             // X-Client
  x_server,             // X-Server
  none
};

std::ostream& operator<<(std::ostream& os, header h);

using headers = std::map<http::header, std::string>;

struct status : public std::exception {
  status() = default;
  status(int code) : code(static_cast<std::uint16_t>(code)) {}
  status(int code, std::string text) : code(static_cast<std::uint16_t>(code)), text(text) {}

  const char* what() const noexcept override;

  std::uint16_t code = 500;
  std::optional<std::string> text;
};

using error = ice::exception_stream<status>;

std::ostream& operator<<(std::ostream& os, const status& s);

//using error = ice::exception_stream<status>;

class version {
public:
  constexpr version() = default;

  constexpr explicit version(std::uint8_t major, std::uint8_t minor = 0) : value_(convert(major, minor)) {}

  constexpr operator bool() const {
    return value_ != 0x0;
  }

  constexpr std::uint8_t value() const {
    return value_;
  }

  constexpr std::uint8_t major() const {
    return value_ >> 4;
  }

  constexpr std::uint8_t minor() const {
    return value_ & 0x0F;
  }

  static constexpr std::uint8_t convert(std::uint8_t major, std::uint8_t minor) {
    return (major << 4) + (minor & 0x0F);
  }

private:
  std::uint8_t value_ = 0x0;
};

constexpr bool operator==(const version& lhs, const version& rhs) {
  return lhs.value() == rhs.value();
}

constexpr bool operator!=(const version& lhs, const version& rhs) {
  return lhs.value() != rhs.value();
}

constexpr bool operator<(const version& lhs, const version& rhs) {
  return lhs.value() < rhs.value();
}

constexpr bool operator>(const version& lhs, const version& rhs) {
  return lhs.value() > rhs.value();
}

constexpr bool operator<=(const version& lhs, const version& rhs) {
  return lhs.value() <= rhs.value();
}

constexpr bool operator>=(const version& lhs, const version& rhs) {
  return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, version v);

using body = std::string;
using endpoint = std::string;

struct path {
  std::filesystem::path filename;
  std::chrono::seconds expires;
  bool must_revalidate = false;

  explicit path(const std::string& filename, std::chrono::seconds expires, bool must_revalidate)
    : filename(filename), expires(std::move(expires)), must_revalidate(must_revalidate) {}
};

using data = std::variant<std::nullptr_t, std::string, ice::json, path>;

class request;
class response;

}  // namespace http
