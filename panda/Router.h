#pragma once

#include <panda/Context.h>
#include <panda/http/Request.h>
#include <vector>

namespace panda {

namespace detail {

const uint8_t MaxMethods = static_cast<uint8_t>(http::Method::DELETE) + 1;

enum class TrieNodeKind { Static, Param };

struct TrieNode {
  TrieNodeKind kind;
  char c;                         // static
  std::string name;               // param
  Handler* handlers[MaxMethods];  // GET, HEAD, PUT, POST, DELETE
  std::vector<std::unique_ptr<TrieNode>> children;

  TrieNode(TrieNodeKind kind, char c);
  TrieNode(TrieNodeKind kind, std::string name);

  void addChild(std::unique_ptr<TrieNode> child);
  TrieNode* getParamChild();
  TrieNode* getStaticChild(char c);
  bool setHandler(http::Method method, Handler* handler);
  Handler* getHandler(http::Method method);

 private:
  void resetHandlers();
};

}  // namespace detail

class Router {
 public:
  static Router& get();

  enum class AddPathResult { OK, Overwrite, Conflict };

  AddPathResult add(http::Method method, const std::string& path,
                    Handler* handler);
  Handler* find(http::Method method, const std::string& path,
                std::vector<std::string>& paramNames,
                std::vector<std::string>& paramValues) const;
  void clear();

 private:
  Router();

  std::unique_ptr<detail::TrieNode> root_;
};

}  // namespace panda