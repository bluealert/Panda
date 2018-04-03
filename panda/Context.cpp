#include <panda/Context.h>

namespace panda {

Context::Context(std::shared_ptr<http::Request> req,
                 std::shared_ptr<http::Response> resp,
                 std::vector<std::string> names, std::vector<std::string> vals)
    : req_(std::move(req)),
      resp_(std::move(resp)),
      names_(std::move(names)),
      values_(std::move(vals)) {}

http::Request &Context::request() const { return *req_; }

http::Response &Context::response() const { return *resp_; }

boost::optional<std::string &> Context::getParam(const std::string &name) {
  for (size_t i = 0; i < names_.size(); i++) {
    if (names_[i] == name) {
      return values_[i];
    }
  }
  return boost::optional<std::string &>{};
}

}  // namespace panda