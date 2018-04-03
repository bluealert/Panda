#pragma once

#include <glog/logging.h>
#include <panda/Context.h>
#include <panda/Pipeline.h>
#include <panda/Router.h>
#include <string>
#include <thread>

namespace panda {

class Panda {
 public:
  explicit Panda(std::size_t concurrency = std::thread::hardware_concurrency());
  void run(const std::string& host, const std::string& service);
  void GET(const std::string& path, Handler* handler);
  void HEAD(const std::string& path, Handler* handler);
  void PUT(const std::string& path, Handler* handler);
  void POST(const std::string& path, Handler* handler);
  void DELETE(const std::string& path, Handler* handler);

 private:
  void checkAddPathResult(http::Method method, const std::string& path,
                          Router::AddPathResult result);

  std::size_t concurrency_;
  std::vector<Pipeline> pipelines_;
  std::vector<std::thread> threads_;
};

}  // namespace panda