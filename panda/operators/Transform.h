#pragma once

#include <boost/optional.hpp>
#include <functional>
#include <type_traits>

namespace panda {
namespace detail {

template <typename Sender, typename Function,
          typename InMsgType =
              typename std::remove_reference_t<Sender>::value_type,
          typename OutMsgType =
              decltype(std::declval<Function>()(std::declval<InMsgType>()))>
class TransformImpl {
 public:
  using value_type = OutMsgType;

  TransformImpl(Sender &sender, Function function)
      : sender_(sender), function_(function) {}

  template <typename EmitFunction>
  void onMessage(EmitFunction emit) {
    emit_ = emit;
    sender_.onMessage([this](InMsgType &&msg) { processMsg(std::move(msg)); });
  }

 private:
  void processMsg(InMsgType &&msg) {
    emit_(std::move(std::invoke(function_, std::move(msg))));
  }

 private:
  Sender &sender_;
  Function function_;
  std::function<void(value_type &&)> emit_;
};

template <typename Function>
struct TransformHelper {
  Function function;
};

}  // namespace detail

namespace operators {

template <typename Sender, typename Function>
auto operator|(Sender &sender,
               detail::TransformHelper<Function> transformation) {
  return detail::TransformImpl<Sender, Function>(sender,
                                                 transformation.function);
}

template <typename Function>
auto transform(Function &&function) {
  return detail::TransformHelper<Function>{std::forward<Function>(function)};
}

}  // namespace operators
}  // namespace panda