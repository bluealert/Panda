#include <panda/http/Response.h>
#include <panda/http/Status.h>
#include <panda/tcp/Channel.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace panda {
namespace http {

using boost::system::error_code;

Response::Response(const std::shared_ptr<tcp::Channel>& channel)
    : channel_(channel) {}

void Response::error(uint16_t code) {
  std::ostringstream oss;
  oss << "HTTP/1.1 " << code << ' ' << http::Status::text(code) << "\r\n";
  oss << "Connection: close\r\n";
  auto rs = oss.str();
  channel_->asyncWrite(rs.c_str(), rs.size(), [](error_code, size_t) {});
  channel_->close();
}

void Response::string(const std::string& s) {
  std::ostringstream oss;
  oss << "HTTP/1.1 " << Status::OK << ' ' << http::Status::text(Status::OK);
  oss << "\r\nContent-Type: text/plain\r\nContent-Length: ";
  oss << s.size() << "\r\n\r\n" << s;
  auto rs = oss.str();
  channel_->asyncWrite(rs.c_str(), rs.size(), [](error_code, size_t) {});
}

void Response::json(const rapidjson::Document& d) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  if (!d.Accept(writer)) {
    error(http::Status::InternalServerError);
    return;
  }

  std::ostringstream oss;
  oss << "HTTP/1.1 " << Status::OK << ' ' << http::Status::text(Status::OK);
  oss << "\r\nContent-Type: application/json\r\nContent-Length: ";
  oss << buffer.GetSize() << "\r\n\r\n";
  oss << buffer.GetString();
  auto rs = oss.str();
  channel_->asyncWrite(rs.c_str(), rs.size(), [](error_code, size_t) {});
}

}  // namespace http
}  // namespace panda