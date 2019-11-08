#pragma once
#include <chrono>
#include <string>
#include <ctime>

namespace http {

using clock = std::chrono::system_clock;

// Formats the time as RFC 1123 "Sun, 06 Nov 1994 08:49:37 GMT".
std::string format(time_t time);

// Formats the time point as RFC 1123 "Sun, 06 Nov 1994 08:49:37 GMT".
std::string format(clock::time_point tp);

// Parses RFC 1123, RFC 1036 or ANSI C date/time into a time point.
clock::time_point parse(const std::string& str);

// Parses RFC 1123 date/time "Sun, 06 Nov 1994 08:49:37 GMT" into a time point.
clock::time_point parse_rfc1123(const std::string& str);

// Parses RFC 1036 date/time "Sunday, 06-Nov-94 08:49:37 GMT" into a time point.
clock::time_point parse_rfc1036(const std::string& str);

// Parses ANSI C date/time "Sun Nov  6 08:49:37 1994" into a time point.
clock::time_point parse_asctime(const std::string& str);

}  // namespace http