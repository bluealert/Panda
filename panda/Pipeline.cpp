#include <glog/logging.h>
#include <panda/Pipeline.h>
#include <panda/Router.h>
#include <panda/http/Status.h>
#include <panda/operators/Sink.h>
#include <panda/operators/Transform.h>

namespace panda {

using namespace boost::asio;
using namespace panda::operators;

using http::Parser11;
using http::Status;

namespace detail {

template <typename Owner, typename Attachment>
Attachment* attachment(Owner& owner) {
  auto attachment = reinterpret_cast<Attachment*>(owner.attachment());
  if (attachment == nullptr) {
    attachment = new Attachment();
    auto deleter = [](uint64_t handle) {
      if (handle) {
        delete reinterpret_cast<Attachment*>(handle);
      }
    };
    owner.setAttachment(reinterpret_cast<uint64_t>(attachment), deleter);
  }
  return attachment;
}

http::Parser11Results parseHTTP(tcp::SourceMsg msg) {
  auto parser = detail::attachment<tcp::Channel, http::Parser11>(*msg.channel);

  http::Parser11Results parserResults;
  if (!parser->append(msg.buf, msg.len)) {
    auto resp = std::make_unique<http::Response>(msg.channel);
    resp->error(Status::InternalServerError);
    return parserResults;
  }

  while (!parser->empty()) {
    auto result = parser->run();
    if (result.status == Parser11::ResultStatus::PartialHeaders ||
        result.status == Parser11::ResultStatus::PartialBody) {
      break;
    }

    auto resp = std::make_unique<http::Response>(msg.channel);
    const uint16_t errTbl[] = {
        Status::BadRequest, Status::MethodNotAllowed, Status::RequestURITooLong,
        Status::RequestHeaderFieldsTooLarge, Status::RequestEntityTooLarge};
    auto statusVal = static_cast<uint8_t>(result.status);
    if (statusVal >= 0 && statusVal < sizeof(errTbl) / sizeof(uint16_t)) {
      resp->error(errTbl[statusVal]);
      break;
    }

    assert(result.status == Parser11::ResultStatus::Finished);

    LOG(INFO) << "parse request finished";
    result.resp = std::move(resp);
    parserResults.push_back(std::move(result));
  }

  return parserResults;
}

struct parseJson {
  http::Parser11Results operator()(http::Parser11Results parserMsgs) {
    for (auto& msg : parserMsgs) {
      if (msg.req->parseBody()) {
        LOG(ERROR) << "parse json failed";
        msg.resp->error(http::Status::BadRequest);
        return http::Parser11Results{};
      }
    }
    return parserMsgs;
  }
};

struct routeHTTP {
  void operator()(http::Parser11Results parserMsgs) {
    for (auto& msg : parserMsgs) {
      std::vector<std::string> names;
      std::vector<std::string> vals;
      names.reserve(4);
      vals.reserve(4);
      auto req = msg.req;
      auto handler =
          Router::get().find(req->method(), req->path(), names, vals);
      if (handler == nullptr) {
        msg.resp->error(http::Status::NotFound);
        break;
      }
      auto ctx = std::make_unique<panda::Context>(
          std::move(req), std::move(msg.resp), std::move(names),
          std::move(vals));
      handler(ctx.get());
    }
  }
};

}  // namespace detail

Pipeline::Pipeline() {
  ios_ = std::make_shared<io_service>();
  idleWork_ = std::make_unique<io_service::work>(*ios_);
}

void Pipeline::run() {
  auto step0 = src_ | transform(detail::parseHTTP);
  auto step1 = step0 | transform(detail::parseJson());
  step1 | sink(detail::routeHTTP());

  ios_->run();
}

void Pipeline::assign(std::shared_ptr<ip::tcp::socket> socket) {
  src_.assign(std::move(socket));
}

std::shared_ptr<io_service>& Pipeline::getIOService() { return ios_; }

}  // namespace panda