#include <panda/IOServicePool.h>

namespace panda {

void IOServicePool::add(const std::shared_ptr<boost::asio::io_service> &ios) {
  ioServices_.push_back(ios);
}

boost::asio::io_service &IOServicePool::get(std::size_t &index) const {
  index = nextIOS_++ % ioServices_.size();
  return *ioServices_[index];
}

}  // namespace panda