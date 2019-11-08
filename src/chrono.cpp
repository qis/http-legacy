#include <http/chrono.hpp>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <ctime>

namespace http {
namespace {

clock::time_point parse(const std::string& str, const char* format) {
  std::tm tm = {};
  std::istringstream iss(str);
  iss >> std::get_time(&tm, format);
#ifdef _MSC_VER
  return clock::from_time_t(_mkgmtime(&tm));
#else
  return clock::from_time_t(timegm(&tm));
#endif
}

}  // namespace

std::string format(time_t time) {
  tm tm = {};
#ifndef _WIN32
  gmtime_r(&time, &tm);
#else
  gmtime_s(&tm, &time);
#endif
  std::ostringstream oss;
  oss << std::put_time(&tm, "%a, %d %b %Y %T GMT");
  return oss.str();
}

std::string format(clock::time_point tp) {
  return format(clock::to_time_t(tp));
}

clock::time_point parse(const std::string& str) {
  // Parse any possible HTTP/1.1 format.
  // See https://tools.ietf.org/html/rfc2616#section-3.3.1 for more information.
  auto pos = str.find_first_not_of(' ');
  if (pos != str.npos && str.size() > pos + 3) {
    switch (str[pos + 3]) {
    case ',':
      return parse_rfc1123(str);
    case ' ':
      return parse_asctime(str);
    default:
      return parse_rfc1036(str);
    }
  }
  throw std::runtime_error("Invalid date/time format.");
  return {};
}

clock::time_point parse_rfc1123(const std::string& str) {
  // Parse the format "Sun, 06 Nov 1994 08:49:37 GMT".
  return parse(str, "%a, %d %b %Y %T GMT");
}

clock::time_point parse_rfc1036(const std::string& str) {
  // Parse the format "Sunday, 06-Nov-94 08:49:37 GMT".
  return parse(str, "%a, %d-%b-%y %T GMT");
}

clock::time_point parse_asctime(const std::string& str) {
  // Parse the format "Sun Nov  6 08:49:37 1994".
  return parse(str, "%a %b %d %T %Y");
}

}  // namespace http
