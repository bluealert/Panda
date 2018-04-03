#include <panda/Router.h>
#include <panda/utils/Path.h>
#include <panda/utils/Slice.h>

namespace panda {

namespace detail {

TrieNode::TrieNode(TrieNodeKind kind, char c) : kind(kind), c(c) {
  resetHandlers();
}

TrieNode::TrieNode(TrieNodeKind kind, std::string name)
    : kind(kind), c(0), name(std::move(name)) {
  resetHandlers();
}

void TrieNode::addChild(std::unique_ptr<TrieNode> child) {
  children.push_back(std::move(child));
}

TrieNode* TrieNode::getParamChild() {
  for (auto& child : children) {
    if (child->kind == TrieNodeKind::Param) {
      return child.get();
    }
  }
  return nullptr;
}

TrieNode* TrieNode::getStaticChild(char c) {
  for (auto& child : children) {
    if (child->kind == TrieNodeKind::Static && child->c == c) {
      return child.get();
    }
  }
  return nullptr;
}

bool TrieNode::setHandler(http::Method method, Handler* handler) {
  auto index = static_cast<int8_t>(method);
  assert(index >= 0 && index <= MaxMethods);
  bool flag = handlers[index] != nullptr;
  handlers[index] = handler;
  return flag;
}

Handler* TrieNode::getHandler(http::Method method) {
  auto index = static_cast<int8_t>(method);
  assert(index >= 0 && index <= MaxMethods);
  return handlers[index];
}

void TrieNode::resetHandlers() { std::fill_n(handlers, MaxMethods, nullptr); }

Router::AddPathResult insert(TrieNode* root, http::Method method,
                             const std::string& s, Handler* handler) {
  utils::Slice path(s);
  path.removePrefix(1);
  TrieNode* currNode = root;
  TrieNode* rawChild = root;
  std::unique_ptr<TrieNode> child = nullptr;
  while (!path.empty()) {
    char c = path[0];
    if (c == ':') {
      size_t i = 0;
      while (++i < path.size() && path[i] != '/') {
      }
      auto paramName = std::string(path.data() + 1, i - 1);
      path.removePrefix(i);

      // one node can only have one param child node
      rawChild = currNode->getParamChild();
      if (rawChild == nullptr) {
        child = std::make_unique<TrieNode>(TrieNodeKind::Param, paramName);
        rawChild = child.get();
      } else if (path.empty()) {
        if (rawChild->name != paramName) {
          return Router::AddPathResult::Conflict;
        }
      }
    } else {
      path.removePrefix(1);

      rawChild = currNode->getStaticChild(c);
      if (rawChild == nullptr) {
        child = std::make_unique<TrieNode>(TrieNodeKind::Static, c);
        rawChild = child.get();
      }
    }
    if (child) {
      currNode->addChild(std::move(child));
    }
    currNode = rawChild;
  }
  if (rawChild->setHandler(method, handler)) {
    return Router::AddPathResult::Overwrite;
  }
  return Router::AddPathResult::OK;
}

Handler* find(TrieNode* root, http::Method method, const std::string& s,
              std::vector<std::string>& paramNames,
              std::vector<std::string>& paramValues) {
  utils::Slice path(s);
  TrieNode* currNode = root;
  path.removePrefix(1);
  while (!path.empty()) {
    char c = path[0];
    auto child = currNode->getStaticChild(c);
    if (child != nullptr) {
      path.removePrefix(1);
    } else {
      child = currNode->getParamChild();
      if (child == nullptr) {
        return nullptr;
      }

      size_t i = 0;
      while (i < path.size() && path[i] != '/') {
        i++;
      }
      auto paramVal = std::string(path.data(), i);
      path.removePrefix(i);

      paramNames.push_back(child->name);
      paramValues.push_back(std::move(paramVal));
    }
    currNode = child;
  }
  return currNode->getHandler(method);
}

}  // namespace detail

Router& Router::get() {
  static Router inst;
  return inst;
}

Router::Router() {
  root_ = std::make_unique<detail::TrieNode>(detail::TrieNodeKind::Static, '/');
}

Router::AddPathResult Router::add(http::Method method, const std::string& path,
                                  Handler* handler) {
  utils::canonicalizePath(const_cast<std::string&>(path));
  return detail::insert(root_.get(), method, path, handler);
}

Handler* Router::find(http::Method method, const std::string& path,
                      std::vector<std::string>& paramNames,
                      std::vector<std::string>& paramValues) const {
  utils::canonicalizePath(const_cast<std::string&>(path));
  return detail::find(root_.get(), method, path, paramNames, paramValues);
}

void Router::clear() {
  root_ = std::make_unique<detail::TrieNode>(detail::TrieNodeKind::Static, '/');
}

}  // namespace panda