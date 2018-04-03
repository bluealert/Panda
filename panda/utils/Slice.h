#pragma once

#include <cassert>
#include <string>

namespace panda {
namespace utils {

class Slice {
 public:
  explicit Slice(const std::string& s);
  Slice(const char* data, size_t size);

  inline const char* data() const { return data_; }
  inline size_t size() const { return size_; }

  inline void removePrefix(size_t n) {
    assert(n > 0 && n <= size_);
    data_ += n;
    size_ -= n;
  }

  inline bool empty() const { return size_ == 0; }

  inline char operator[](size_t index) const {
    assert(index >= 0 && index < size_);
    return data_[index];
  }

 private:
  const char* data_;
  size_t size_;
};

}  // namespace utils
}  // namespace panda