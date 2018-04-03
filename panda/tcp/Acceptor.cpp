#include <glog/logging.h>
#include <panda/Config.h>
#include <panda/tcp/Acceptor.h>

namespace panda {
namespace tcp {

using namespace boost::asio;
using boost::system::error_code;

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
  auto handler = [this](const error_code& ec) {
    if (!ec) {
      LOG(INFO) << "Accept connection: "
                << socket_->remote_endpoint().address().to_string() << ":"
                << socket_->remote_endpoint().port();
      handler_(std::move(socket_), index_);
    } else {
      LOG(ERROR) << "async_accept failed: " << ec.message();
    }
    doAccept();
  };

  socket_ = std::make_unique<ip::tcp::socket>(iosPool_.get(index_));
  acceptor_.async_accept(*socket_, handler);
}

}  // namespace tcp
}  // namespace panda