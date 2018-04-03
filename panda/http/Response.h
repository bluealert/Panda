#pragma once

#include <rapidjson/document.h>
#include <memory>

namespace panda {

namespace tcp {
class Channel;
}

namespace http {

class Response {
 public:
  explicit Response(const std::shared_ptr<tcp::Channel>& channel);

  void error(uint16_t code);
  void string(const std::string& s);
  void json(const rapidjson::Document& d);

 private:
  std::shared_ptr<tcp::Channel> channel_;
};

}  // namespace http
}  // namespace panda