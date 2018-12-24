#pragma once

#include <panda/http/Parser11.h>
#include <panda/tcp/Source.h>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace panda {

class Pipeline {
 public:
  Pipeline();

  void run();
  void assign(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
  std::shared_ptr<boost::asio::io_service>& getIOService();

 private:
  template <typename CompletionHandler>
  void post(CompletionHandler handler) {
    ios_->post(handler);
  }

 private:
  tcp::Source src_;
  std::shared_ptr<boost::asio::io_service> ios_;
  std::unique_ptr<boost::asio::io_service::work> idleWork_;
};

}  // namespace panda