#pragma once

#include <glog/logging.h>
#include <panda/Config.h>
#include <boost/asio/ip/tcp.hpp>
#include <functional>

namespace panda {
namespace tcp {

class Channel {
 public:
  using AttachmentDeleter = std::function<void(uint64_t)>;

  explicit Channel(std::unique_ptr<boost::asio::ip::tcp::socket> sock);

  template <typename ReadHandler>
  void asyncRead(char* buf, size_t len, ReadHandler handler) {
    auto readHandler = [buf, len, handler, this](boost::system::error_code err,
                                                 size_t size) {
      if (err) {
        LOG(ERROR) << "asyncRead failed: " << err.message();
        handler(err, 0);
        return;
      }
      handler(boost::system::error_code(), size);
      asyncRead(buf, len, handler);
    };
    sock_->async_read_some(boost::asio::buffer(buf, len), readHandler);
  }

  template <typename WriteHandler>
  void asyncWrite(const char* buf, size_t len, WriteHandler handler) {
    auto writeHandler = [buf, len, handler, this](boost::system::error_code err,
                                                  size_t size) {
      if (err) {
        LOG(ERROR) << "asyncWrite failed: " << err.message();
        handler(err, len);
        return;
      }
      size_t avail = len - size;
      if (avail <= 0) {
        handler(boost::system::error_code(), 0);
        return;
      }
      asyncWrite(buf + size, avail, handler);
    };
    sock_->async_write_some(boost::asio::buffer(buf, len), writeHandler);
  }

  void close();

  void setAttachment(uint64_t handle, AttachmentDeleter deleter);
  uint64_t attachment();

 private:
  bool closed;
  uint64_t attachment_;
  AttachmentDeleter deleter_;
  std::unique_ptr<boost::asio::ip::tcp::socket> sock_;
};

}  // namespace tcp
}  // namespace panda