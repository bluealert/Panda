#include <panda/utils/Path.h>
#include <sstream>

namespace panda {
namespace utils {

void canonicalizePath(std::string& path) {
  if (path.empty()) {
    return;
  }

  size_t i = 0;
  std::ostringstream oss;
  if (path[0] == '/') {
    while (++i < path.size() && path[i] == '/') {
    }
  }
  oss << '/';
  for (; i < path.size(); i++) {
    if (path[i] != '/') {
      oss << path[i];
      continue;
    }

    size_t j = i;
    while (++j < path.size() && path[j] == '/') {
    }
    i = j - 1;
    if (i != path.size() - 1) {
      oss << path[i];
    }
  }
  path = oss.str();
}

}  // namespace utils
}  // namespace panda