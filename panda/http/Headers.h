#pragma once

#include <string>

namespace panda {
namespace http {

class Headers {
 public:
  static constexpr char ContentType[] = "Content-Type";
  static constexpr char ContentLength[] = "Content-Length";
  static constexpr char ContentEncoding[] = "Content-Encoding";
};

}  // namespace http
}  // namespace panda