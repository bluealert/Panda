#pragma once

#include <panda/http/Request.h>
#include <panda/http/Response.h>
#include <boost/optional/optional.hpp>
#include <vector>

namespace panda {

class Panda;
class Context;

using Handler = void(Context* c);

class Context {
 public:
  Context(std::shared_ptr<http::Request> req,
          std::shared_ptr<http::Response> resp, std::vector<std::string> names,
          std::vector<std::string> vals);

  http::Request& request() const;
  http::Response& response() const;
  boost::optional<std::string&> getParam(const std::string& name);

 private:
  std::shared_ptr<http::Request> req_;
  std::shared_ptr<http::Response> resp_;
  std::vector<std::string> names_;
  std::vector<std::string> values_;
};

}  // namespace panda