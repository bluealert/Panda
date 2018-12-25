#include <glog/logging.h>
#include <panda/Config.h>
#include <panda/tcp/Acceptor.h>

namespace panda {
namespace tcp {

Acceptor::Acceptor(IOServicePool& iosPool)
    : iosPool_(iosPool), acceptor_(ios_) {}

void Acceptor::run(std::string host, std::string service,
                   AcceptHandler handler) {
  handler_ = std::move(handler);

  error_code err;
  ip::tcp::resolver resolver(ios_);
  auto result = resolver.resolve({host, service}, err);
  if (err) {
    LOG(FATAL) << "Resolve host and service failed: " << host << ":" << service;
  }

  auto endpoint = result->endpoint();
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen(Config::AcceptorBacklog);
  LOG(INFO) << "Listening at: " << endpoint.address().to_string() << ":"
            << endpoint.port() << ", pid: " << getpid();

  doAccept();

  ios_.run();
}

void Acceptor::doAccept() {
  std::uint16_t index;
  auto& ios = iosPool_.get(index);
  sock_ = std::make_unique<ip::tcp::socket>(ios);
  acceptor_.async_accept(*sock_, [this, index](const error_code& ec) {
    if (!ec) {
      LOG(INFO) << "Accept connection: "
                << sock_->remote_endpoint().address().to_string() << ":"
                << sock_->remote_endpoint().port();
      handler_(std::move(sock_), error_code(), index);
    } else {
      handler_(nullptr, ec, -1);
      LOG(ERROR) << "async_accept failed: " << ec.message();
    }
    doAccept();
  });
}

}  // namespace tcp
}  // namespace panda