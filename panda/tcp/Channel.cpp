#include <panda/Config.h>
#include <panda/tcp/Channel.h>

namespace panda {
namespace tcp {

using namespace boost::asio;
using boost::system::error_code;

Channel::Channel(std::shared_ptr<ip::tcp::socket> sock)
    : closed(false), attachment_(0), deleter_(nullptr), sock_(std::move(sock)) {
  error_code err;
  sock_->set_option(ip::tcp::no_delay{true}, err);
  if (err) {
    LOG(ERROR) << "Set no_delay failed: " << err.message();
  }
  socket_base::receive_buffer_size recvOpt{Config::TcpBufferSize};
  sock_->set_option(recvOpt, err);
  if (err) {
    LOG(ERROR) << "Set receive buffer size failed: " << err.message();
  }
  socket_base::send_buffer_size sendOpt{Config::TcpBufferSize};
  sock_->set_option(sendOpt, err);
  if (err) {
    LOG(ERROR) << "Set send buffer size failed: " << err.message();
  }
}

void Channel::close() {
  if (closed) {
    return;
  }
  closed = true;
  if (deleter_ != nullptr) {
    deleter_(attachment_);
  }
  error_code err;
  sock_->close(err);
}

void Channel::setAttachment(uint64_t handle,
                            Channel::AttachmentDeleter deleter) {
  attachment_ = handle;
  deleter_ = std::move(deleter);
}

uint64_t Channel::attachment() { return attachment_; }

}  // namespace tcp
}  // namespace panda