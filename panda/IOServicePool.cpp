#include <panda/IOServicePool.h>

namespace panda {

void IOServicePool::add(const std::shared_ptr<boost::asio::io_service> &ios) {
  ioServices_.push_back(ios);
}

boost::asio::io_service &IOServicePool::get(std::uint16_t &index) {
  index = nextIOS_++ % static_cast<uint16_t>(ioServices_.size());
  return *ioServices_[index];
}

}  // namespace panda