#pragma once

#include <panda/IOServicePool.h>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace panda {
namespace tcp {

using namespace boost::asio;
using boost::system::error_code;

using AcceptHandler = std::function<void(std::unique_ptr<ip::tcp::socket>,
                                         const error_code& ec, std::uint16_t)>;

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
  ip::tcp::acceptor acceptor_;
  std::unique_ptr<ip::tcp::socket> sock_;
};

}  // namespace tcp
}  // namespace panda