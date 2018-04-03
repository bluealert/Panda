#pragma once

#include <functional>
#include <type_traits>

namespace panda {

namespace detail {

template <typename Sender, typename Function,
          typename MsgType =
              typename std::remove_reference_t<Sender>::value_type>
class SinkImpl {
 public:
  using value_type = MsgType;

  SinkImpl(Sender &sender, Function function)
      : sender_(sender), function_(function) {
    sender_.onMessage([this](MsgType &&msg) { processMsg(std::move(msg)); });
  }

 private:
  void processMsg(MsgType &&msg) { std::invoke(function_, std::move(msg)); }

 private:
  Sender &sender_;
  Function function_;
};

template <typename Function>
struct SinkHelper {
  Function function;
};

}  // namespace detail

namespace operators {

template <typename Sender, typename Function>
auto operator|(Sender &sender, detail::SinkHelper<Function> sink) {
  return detail::SinkImpl<Sender, Function>(sender, sink.function);
};

template <typename Function>
auto sink(Function &&function) {
  return detail::SinkHelper<Function>{std::forward<Function>(function)};
}

}  // namespace operators

}  // namespace panda