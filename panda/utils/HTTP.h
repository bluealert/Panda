#pragma once

#include <panda/http/Request.h>

namespace panda {
namespace utils {

class HTTP {
 public:
  static std::string MethodToStr(http::Method method);
};

}  // namespace utils
}  // namespace panda