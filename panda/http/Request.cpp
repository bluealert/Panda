#include <panda/http/Request.h>

namespace panda {
namespace http {

Request::Request() : method_(Method::NONE) {}

Request::Request(Method method, std::string uri, HeadersType headers)
    : method_(method), uri_(std::move(uri)), headers_(std::move(headers)) {}

void Request::setBody(std::string body) { body_ = std::move(body); }

Method Request::method() const { return method_; }

const std::string& Request::path() const { return uri_; }

boost::optional<std::string&> Request::header(const std::string& name) {
  auto it = headers_.find(name);
  if (it != headers_.end()) {
    return it->second;
  }
  return boost::optional<std::string&>{};
}

rapidjson::Document& Request::body() { return jsonBody_; }

bool Request::parseBody() {
  if (body_.empty()) {
    return false;
  }
  auto ok = jsonBody_.Parse(body_.c_str(), body_.size()).HasParseError();
  body_.clear();
  return ok;
}

}  // namespace http
}  // namespace panda