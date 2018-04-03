#include <panda/utils/Slice.h>

namespace panda {
namespace utils {

Slice::Slice(const std::string &s) : data_(s.c_str()), size_(s.length()) {}

Slice::Slice(const char *data, size_t size) : data_(data), size_(size) {}

}  // namespace utils
}  // namespace panda