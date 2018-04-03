#pragma once

#include <functional>

namespace panda {
namespace detail {

template <typename Sender, typename Predicate,
          typename MsgType = typename Sender::value_type>
class FilterImpl {
 public:
  using value_type = MsgType;

  FilterImpl(Sender&& sender, Predicate predicate)
      : sender_(std::move(sender)), predicate_(predicate) {}

  template <typename EmitFunction>
  void onMessage(EmitFunction emit) {
    emit_ = emit;
    sender_.onMessage([this](MsgType&& msg) { processMsg(std::move(msg)); });
  }

 private:
  void processMsg(MsgType&& msg) const {
    if (std::invoke(predicate_, msg)) {
      emit_(std::move(msg));
    }
  }

 private:
  Sender sender_;
  Predicate predicate_;
  std::function<void(MsgType&&)> emit_;
};

template <typename Predicate>
struct FilterHelper {
  Predicate predicate;
};

}  // namespace detail

namespace operators {

template <typename Sender, typename Predicate>
auto operator|(Sender&& sender, detail::FilterHelper<Predicate> filter) {
  return detail::FilterImpl<Sender, Predicate>(std::forward<Sender>(sender),
                                               filter.predicate);
}

template <typename Predicate>
auto filter(Predicate&& predicate) {
  return detail::FilterHelper<Predicate>{std::forward<Predicate>(predicate)};
}

}  // namespace operators

}  // namespace panda