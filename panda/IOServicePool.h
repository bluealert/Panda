#pragma once

#include <boost/asio/io_service.hpp>

namespace panda {

class IOServicePool {
 public:
  void add(const std::shared_ptr<boost::asio::io_service> &ios);
  boost::asio::io_service &get(std::uint16_t &index);

 private:
  std::atomic<std::uint16_t> nextIOS_{0};
  std::vector<std::shared_ptr<boost::asio::io_service>> ioServices_;
};

}  // namespace panda