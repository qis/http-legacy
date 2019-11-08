#pragma once
#include <http/types.hpp>
#include <ice/uuid.hpp>
#include <optional>
#include <string>

namespace http {

class request {
public:
  request() = default;

  http::method method = http::method::none;
  std::string path;
  http::query query;
  bool directory = false;
  http::version version;
  http::headers headers;
  http::body body;
  std::string client;
  std::string server;
  ice::uuid session;

  ice::json data() const {
    if (!body.empty()) {
      return ice::json::parse(body);
    }
    if (query && !query.value().empty()) {
      return ice::json::parse(query.value());
    }
    return {};
  }

  void clear() {
    method = http::method::none;
    path.clear();
    query = {};
    directory = false;
    version = {};
    headers.clear();
    body.clear();
    client.clear();
    server.clear();
    session = {};
  }
};

}  // namespace http
