#include <glog/logging.h>
#include <panda/http/Headers.h>
#include <panda/http/MIMETypes.h>
#include <panda/http/Parser11.h>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace panda {
namespace http {

bool Parser11::append(const char *buf, size_t size) {
  if (size <= 0 || wpos_ + size > cap_) {
    return false;
  }

  std::memcpy(buf_ + wpos_, buf, size);
  wpos_ += size;
  return true;
}

bool Parser11::empty() const { return rpos_ == wpos_; }

Parser11::Result Parser11::run() {
  Method method2 = Method::NONE;
  std::string uri;
  HeadersType headers2;

  while (true) {
    switch (state_) {
      case HTTP11ParserState::PartialHeaders: {
        const char *method = nullptr;
        const char *path = nullptr;
        size_t methodLen = 0, pathLen = 0;
        int minorVer = 0;
        struct phr_header headers[Config::MaxHeaders];
        size_t headersNum = sizeof(headers) / sizeof(headers[0]);
        int ret = phr_parse_request(
            buf_ + rpos_, static_cast<size_t>(wpos_ - rpos_), &method,
            &methodLen, &path, &pathLen, &minorVer, headers, &headersNum, 0);
        if (ret == -1) {
          LOG(ERROR) << "phr_parse_request failed";
          goto error;
        }
        if (ret == -2) {
          if (static_cast<size_t>(wpos_ - rpos_) >= Config::MaxReqHeadersSize) {
            return Result{.status = ResultStatus::HeadersTooLarge};
          }

          shrinkBuf();
          return Result{.status = ResultStatus::PartialHeaders};
        }

        if (pathLen >= Config::MaxURILength) {
          return Result{.status = ResultStatus::URITooLong};
        }

        rpos_ += ret;

        method2 = toMethod(method, methodLen);
        if (method2 == Method::NONE || method2 == Method::CONNECT ||
            method2 == Method::OPTIONS || method2 == Method::TRACE ||
            method2 == Method::PATCH) {
          return Result{.status = ResultStatus::MethodNotAllowed};
        }

        uri = std::string(path, pathLen);

        if (!toHeaders(headers, headersNum, headers2)) {
          LOG(ERROR) << "toHeaders failed";
          goto error;
        }

        if (method2 == Method::POST || method2 == Method::PUT ||
            method2 == Method::DELETE) {
          // Content-Encoding
          if (headers2.find(Headers::ContentEncoding) != headers2.end()) {
            LOG(ERROR) << "don't support any content encoding now";
            goto error;
          }

          // Content-Type
          auto it = headers2.find(Headers::ContentType);
          if (it == headers2.end()) {
            LOG(ERROR) << "don't have Content-Type";
            goto error;
          }
          if (it->second != MIMETypes::application_json &&
              it->second != MIMETypes::text_json) {
            LOG(ERROR) << "only support json";
            goto error;
          }

          // Content-Length
          it = headers2.find(Headers::ContentLength);
          if (it == headers2.end()) {
            LOG(ERROR) << "don't have Content-Length";
            goto error;
          }
          try {
            contentLength_ = std::stoi(it->second);
          } catch (const std::exception &e) {
            LOG(ERROR) << "invalid Content-Length";
            goto error;
          }
          if (contentLength_ < 0 ||
              static_cast<size_t>(contentLength_) >= Config::MaxReqBodySize) {
            return Result{.status = ResultStatus::BodyTooLarge};
          }
        }

        req_ = std::make_unique<Request>(method2, uri, headers2);

        if (contentLength_ == 0) {
          goto finish;
        }
        if (method2 == Method::GET || method2 == Method::HEAD) {
          if (contentLength_ > 0) {
            LOG(ERROR) << "invalid Content-Length";
            goto error;
          }
          goto finish;
        }

        state_ = HTTP11ParserState::PartialBody;
        break;
      }
      case HTTP11ParserState::PartialBody: {
        auto avail = wpos_ - rpos_;
        assert(avail >= 0);
        if (avail < 0) {
          LOG(ERROR) << "invalid Parser11 state";
          goto error;
        }

        body_.write(buf_ + rpos_, static_cast<size_t>(avail));
        if (avail < contentLength_) {
          rpos_ = 0;
          wpos_ = 0;
          contentLength_ -= avail;
          return Result{.status = ResultStatus::PartialBody};
        } else {
          rpos_ += contentLength_;
          contentLength_ = 0;
          req_->setBody(body_.str());
          goto finish;
        }
      }
    }
  }

error:
  return Result{.status = ResultStatus::Error};

finish:
  state_ = HTTP11ParserState::PartialHeaders;

  assert(wpos_ - rpos_ >= 0);

  Result msg;
  msg.status = ResultStatus::Finished;
  msg.req = std::move(req_);
  return msg;
}

Method Parser11::toMethod(const char *buf, size_t len) {
  std::string httpMethod(buf, len);
  boost::to_upper(httpMethod);
  const std::map<std::string, Method> methodTable = {
      {"GET", Method::GET},         {"HEAD", Method::HEAD},
      {"POST", Method::POST},       {"PUT", Method::PUT},
      {"DELETE", Method::DELETE},   {"CONNECT", Method::CONNECT},
      {"OPTIONS", Method::OPTIONS}, {"TRACE", Method::TRACE},
      {"PATCH", Method::PATCH}};
  auto it = methodTable.find(httpMethod);
  if (it == methodTable.end()) {
    return Method::NONE;
  }
  return it->second;
}

bool Parser11::toHeaders(struct phr_header *headers, size_t num,
                         HeadersType &headers2) {
  for (size_t i = 0; i != num; ++i) {
    std::string name(headers[i].name, headers[i].name_len);
    std::string value(headers[i].value, headers[i].value_len);
    boost::trim(name);
    if (name.empty()) {
      return false;
    }
    boost::trim(value);
    headers2.insert(std::make_pair(std::move(name), std::move(value)));
  }
  return true;
}

void Parser11::shrinkBuf() {
  if (rpos_ > 0) {
    auto remain = wpos_ - rpos_;
    if (remain > 0) {
      ::memmove(buf_, buf_ + rpos_, static_cast<size_t>(remain));
    }
    rpos_ = 0;
    wpos_ = remain;
  }
}

}  // namespace http
}  // namespace panda