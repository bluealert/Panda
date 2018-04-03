#include <panda/utils/HTTP.h>

namespace panda {
namespace utils {

std::string HTTP::MethodToStr(http::Method method) {
  static const std::string methodTbl[] = {"GET", "HEAD", "PUT", "POST",
                                          "DELETE"};
  const auto index = static_cast<uint8_t>(method);
  return methodTbl[index];
}

}  // namespace utils
}  // namespace panda