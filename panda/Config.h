#pragma once

#include <cstddef>

namespace panda {

class Config {
 public:
  static constexpr size_t AcceptorBacklog = 512;
  static constexpr size_t TcpBufferSize = 1024 * 32;

  static constexpr size_t MaxHeaders = 32;
  static constexpr size_t MaxURILength = 1024 * 2;
  static constexpr size_t MaxReqHeadersSize = 1024 * 8;
  static constexpr size_t MaxReqBodySize = 1024 * 1024 * 1;
  static constexpr size_t Parser11BufSize =
      Config::MaxReqHeadersSize + Config::TcpBufferSize;
};

}  // namespace panda