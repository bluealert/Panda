#include <panda/Panda.h>
#include <panda/tcp/Acceptor.h>
#include <panda/utils/HTTP.h>

namespace panda {

using namespace boost::asio;
using boost::system::error_code;

Panda::Panda(std::size_t concurrency) {
  google::InitGoogleLogging("Panda");
  FLAGS_minloglevel = 3;
  FLAGS_logtostderr = true;
  FLAGS_colorlogtostderr = true;

  std::size_t maxConcurrency = std::thread::hardware_concurrency();
  if (maxConcurrency == 0) {
    maxConcurrency = 2;
  }
  if (concurrency <= 0 || concurrency > maxConcurrency) {
    concurrency = maxConcurrency;
  }
  concurrency_ = concurrency;
}

void Panda::run(const std::string &host, const std::string &service) {
  IOServicePool iosPool;
  for (size_t i = 0; i < concurrency_; i++) {
    pipelines_.emplace_back();
  }
  for (auto &pipeline : pipelines_) {
    iosPool.add(pipeline.getIOService());
    threads_.emplace_back([&pipeline]() { pipeline.run(); });
  }
  tcp::Acceptor acceptor(iosPool);
  auto acceptHandler = [this](std::unique_ptr<ip::tcp::socket> sock,
                              const error_code &ec, std::uint16_t index) {
    pipelines_[index].assign(std::move(sock));
  };
  acceptor.run(host, service, acceptHandler);
}

void Panda::GET(const std::string &path, Handler *handler) {
  auto result = Router::get().add(http::Method::GET, path, handler);
  checkAddPathResult(http::Method::GET, path, result);
}

void Panda::HEAD(const std::string &path, Handler *handler) {
  auto result = Router::get().add(http::Method::HEAD, path, handler);
  checkAddPathResult(http::Method::HEAD, path, result);
}

void Panda::PUT(const std::string &path, Handler *handler) {
  auto result = Router::get().add(http::Method::PUT, path, handler);
  checkAddPathResult(http::Method::PUT, path, result);
}

void Panda::POST(const std::string &path, Handler *handler) {
  auto result = Router::get().add(http::Method::POST, path, handler);
  checkAddPathResult(http::Method::POST, path, result);
}

void Panda::DELETE(const std::string &path, Handler *handler) {
  auto result = Router::get().add(http::Method::DELETE, path, handler);
  checkAddPathResult(http::Method::DELETE, path, result);
}

void Panda::checkAddPathResult(http::Method method, const std::string &path,
                               Router::AddPathResult result) {
  if (result == Router::AddPathResult::Overwrite) {
    LOG(WARNING) << "(" << utils::HTTP::MethodToStr(method) << ", " << path
                 << ") overwrite previous route.";
  } else if (result == Router::AddPathResult::Conflict) {
    LOG(FATAL) << "(" << utils::HTTP::MethodToStr(method) << ", " << path
               << ") conflict to previous route.";
  }
}

}  // namespace panda