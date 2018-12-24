#pragma once

#include <panda/IOServicePool.h>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace panda {
namespace tcp {

using AcceptHandler = std::function<void(
    std::shared_ptr<boost::asio::ip::tcp::socket>, std::uint16_t)>;

class Acceptor {
 public:
  explicit Acceptor(IOServicePool& iosPool);

  void run(std::string host, std::string service, AcceptHandler handler);

 private:
  void doAccept();

 private:
  IOServicePool& iosPool_;
  AcceptHandler handler_;
  boost::asio::io_service ios_;
  boost::asio::ip::tcp::acceptor acceptor_;
};

}  // namespace tcp
}  // namespace panda