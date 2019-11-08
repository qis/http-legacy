// Compile this file with re2c version >= 0.16:
//
//   re2c -o parse.hpp parse.hpp.re
//

#pragma once
#include <http/types.hpp>
#include <string>

namespace http {
namespace detail {

inline header parse_header(const std::string& name) {
  const char* YYCURSOR = name.data();
  const char* YYMARKER = YYCURSOR;

  /*!re2c

  re2c:define:YYCTYPE = "char";
  re2c:yyfill:enable = 0;

  *                   { return header::none; }
  'Accept-Encoding'   { return header::accept_encoding; }
  'Cache-Control'     { return header::cache_control; }
  'Connection'        { return header::connection; }
  'Content-Encoding'  { return header::content_encoding; }
  'Content-Type'      { return header::content_type; }
  'Content-Length'    { return header::content_length; }
  'Cookie'            { return header::cookie; }
  'Date'              { return header::date; }
  'Expect'            { return header::expect; }
  'Expires'           { return header::expires; }
  'Host'              { return header::host; }
  'If-Modified-Since' { return header::if_modified_since; }
  'Last-Modified'     { return header::last_modified; }
  'Location'          { return header::location; }
  'Origin'            { return header::origin; }
  'Pragma'            { return header::pragma; }
  'Refresh'           { return header::refresh; }
  'Server'            { return header::server; }
  'Set-Cookie'        { return header::set_cookie; }
  'Transfer-Encoding' { return header::transfer_encoding; }
  'User-Agent'        { return header::user_agent; }
  'X-Client'          { return header::x_client; }
  'X-Server'          { return header::x_server; }

  */
}

}  // namespace detail
}  // namespace http

// vim:ft=cpp
