#include <glog/logging.h>
#include <panda/Config.h>
#include <panda/tcp/Channel.h>
#include <panda/tcp/Source.h>

namespace panda {
namespace tcp {

using namespace boost::asio;
using boost::system::error_code;

namespace detail {

template <typename EmitFunction>
class TcpSession
    : public std::enable_shared_from_this<TcpSession<EmitFunction>> {
 public:
  TcpSession(std::unique_ptr<ip::tcp::socket> sock, EmitFunction emit)
      : emit_(emit) {
    channel_ = std::make_shared<tcp::Channel>(std::move(sock));
  }

  void start() { doRead(); }

 private:
  using SharedSession = std::enable_shared_from_this<TcpSession<EmitFunction>>;

  void doRead() {
    auto self = SharedSession::shared_from_this();
    auto handler = [this, self](const error_code& err, std::size_t size) {
      if (err) {
        channel_->close();
        return;
      }
      if (size <= 0) {
        LOG(ERROR) << "asyncRead read zero";
        return;
      }

      LOG(INFO) << "asyncRead: " << size;

      emit_(SourceMsg{.channel = channel_, .buf = buf_, .len = size});

      doRead();
    };

    channel_->asyncRead(buf_, cap_, handler);
  }

  EmitFunction emit_;
  char buf_[Config::TcpBufferSize];
  size_t cap_ = Config::TcpBufferSize;
  std::shared_ptr<tcp::Channel> channel_;
};

template <typename Socket, typename EmitFunction>
auto makeTcpSession(Socket&& socket, EmitFunction&& emit) {
  return std::make_shared<TcpSession<EmitFunction>>(
      std::forward<Socket>(socket), std::forward<EmitFunction>(emit));
}

}  // namespace detail

void Source::assign(std::unique_ptr<ip::tcp::socket> sock) {
  detail::makeTcpSession(std::move(sock), emit_)->start();
}

}  // namespace tcp
}  // namespace panda