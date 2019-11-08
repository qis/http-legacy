#pragma once
#include <http/request.hpp>
#include <http/response.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

namespace http {

class server {
public:
  server(const std::string& address, const std::string& service, bool reuse_address = true, std::size_t root = 0);

  server(server&& other) = default;
  server(const server& other) = delete;

  server& operator=(server&& other) = default;
  server& operator=(const server& other) = delete;

  virtual ~server();

  void queue(std::string name, std::chrono::system_clock::time_point expiry_time, std::function<void()> handler);
  void queue(std::string name, std::chrono::milliseconds expiry_time, std::function<void()> handler);
  void abort(std::string name);

  std::string endpoint() const;

  void run(std::size_t threads = 1);
  void stop();

  virtual bool debug() const {
    return false;
  }

  virtual bool query() const {
    return false;
  }

  virtual response handle(request& request) = 0;

private:
  class impl;
  std::unique_ptr<impl> impl_;
};

}  // namespace http
