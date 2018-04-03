#pragma once

#include <rapidjson/document.h>
#include <boost/optional/optional.hpp>
#include <sstream>
#include <string>
#include <unordered_map>

namespace panda {
namespace http {

enum class Method : int8_t {
  NONE = -1,
  GET,
  HEAD,
  PUT,
  POST,
  DELETE,
  CONNECT,
  OPTIONS,
  TRACE,
  PATCH
};

using HeadersType = std::unordered_map<std::string, std::string>;

class Request {
 public:
  Request();
  Request(Method method, std::string uri, HeadersType headers);

  void setBody(std::string body);

  Method method() const;
  const std::string& path() const;
  boost::optional<std::string&> header(const std::string& name);
  rapidjson::Document& body();
  bool parseBody();

 private:
  Method method_;
  std::string uri_;
  HeadersType headers_;
  std::string body_;
  rapidjson::Document jsonBody_;
};

}  // namespace http
}  // namespace panda