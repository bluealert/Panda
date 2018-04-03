#pragma once

#include <panda/Config.h>
#include <panda/http/Request.h>
#include <panda/http/Response.h>
#include <picohttpparser.h>
#include <cstddef>
#include <map>

namespace panda {
namespace http {

class Parser11 {
 public:
  enum class ResultStatus : uint8_t {
    Error = 0,         // 400 Bad Request
    MethodNotAllowed,  // 405 Method Not Allowed
    URITooLong,        // 414 Request URI Too Long
    HeadersTooLarge,   // 431 Request Header Fields Too Large
    BodyTooLarge,      // 413 Request Entity Too Large
    PartialHeaders,
    PartialBody,
    Finished
  };

  struct Result {
    ResultStatus status;
    std::shared_ptr<Request> req;
    std::shared_ptr<Response> resp;
  };

  bool append(const char* buf, size_t size);
  bool empty() const;
  Result run();

 private:
  inline Method toMethod(const char* buf, size_t len);
  inline bool toHeaders(struct phr_header* headers, size_t num,
                        HeadersType& headers2);
  inline void shrinkBuf();

  enum class HTTP11ParserState { PartialHeaders, PartialBody };

  char buf_[Config::Parser11BufSize];
  int32_t rpos_{0}, wpos_{0}, contentLength_{0};
  size_t cap_{Config::Parser11BufSize};
  HTTP11ParserState state_{HTTP11ParserState::PartialHeaders};
  std::unique_ptr<Request> req_;
  std::ostringstream body_;
};

using Parser11Results = std::vector<Parser11::Result>;

}  // namespace http
}  // namespace panda