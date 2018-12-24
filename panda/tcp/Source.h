#pragma once

#include <panda/tcp/Channel.h>
#include <boost/asio/ip/tcp.hpp>
#include <functional>

namespace panda {
namespace tcp {

struct SourceMsg {
  std::shared_ptr<tcp::Channel>& channel;
  const char* buf;
  size_t len;
};

class Source {
 public:
  using value_type = SourceMsg;

  void assign(std::shared_ptr<boost::asio::ip::tcp::socket> sock);

  template <typename EmitFunction>
  void onMessage(EmitFunction emit) {
    emit_ = emit;
  }

 private:
  std::function<void(value_type)> emit_;
};

}  // namespace tcp
}  // namespace panda