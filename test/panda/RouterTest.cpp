#include <gtest/gtest.h>
#include <panda/Router.h>

namespace panda {

using http::Method;

TEST(RouterTest, TestPathMatch0) {
  Router::get().clear();
  ASSERT_TRUE(
      Router::AddPathResult::OK ==
      Router::get().add(Method::GET, ":param///:param", [](Context* c) {}));

  std::vector<std::string> names;
  std::vector<std::string> vals;
  ASSERT_TRUE(Router::get().find(Method::GET, "////1/2////", names, vals));
  ASSERT_EQ(names.size(), 2);
  ASSERT_EQ(names[0], "param");
  ASSERT_EQ(names[1], "param");
  ASSERT_EQ(vals[0], "1");
  ASSERT_EQ(vals[1], "2");
}

TEST(RouterTest, TestPathMatch1) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "hello///world//:param///:param",
                              [](Context* c) {}));
  std::vector<std::string> names;
  std::vector<std::string> vals;
  ASSERT_TRUE(Router::get().find(Method::GET, "/hello/world/1/2", names, vals));
  ASSERT_EQ(names.size(), 2);
  ASSERT_EQ(names[0], "param");
  ASSERT_EQ(names[1], "param");
  ASSERT_EQ(vals[0], "1");
  ASSERT_EQ(vals[1], "2");
}

TEST(RouterTest, TestPathAdd0) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users/:id", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users/new", [](Context* c) {}));
}

TEST(RouterTest, TestPathAdd1) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users/new", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users/:id", [](Context* c) {}));
}

TEST(RouterTest, TestPathAdd2) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users/:new", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::Overwrite,
            Router::get().add(Method::GET, "/users/:new", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::Conflict,
            Router::get().add(Method::GET, "/users/:id", [](Context* c) {}));
}

TEST(RouterTest, TestPathFind0) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/", [](Context* c) {}));

  std::vector<std::string> names;
  std::vector<std::string> vals;
  ASSERT_TRUE(Router::get().find(Method::GET, "/", names, vals));
}

TEST(RouterTest, TestPathFind1) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::HEAD, "/users", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::PUT, "/users", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::Overwrite,
            Router::get().add(Method::PUT, "/users", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::POST, "/users", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::DELETE, "/users", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::Overwrite,
            Router::get().add(Method::DELETE, "/users", [](Context* c) {}));

  std::vector<std::string> names;
  std::vector<std::string> vals;
  ASSERT_TRUE(Router::get().find(Method::GET, "/users", names, vals));
  ASSERT_TRUE(Router::get().find(Method::HEAD, "/users", names, vals));
  ASSERT_TRUE(Router::get().find(Method::PUT, "/users", names, vals));
  ASSERT_TRUE(Router::get().find(Method::POST, "/users", names, vals));
  ASSERT_TRUE(Router::get().find(Method::DELETE, "/users", names, vals));
}

TEST(RouterTest, TestPathFind2) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users/:tid", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::POST, "/users/new", [](Context* c) {}));

  std::vector<std::string> names;
  std::vector<std::string> vals;
  ASSERT_TRUE(Router::get().find(Method::GET, "/users/100", names, vals));
  ASSERT_EQ(names.size(), 1);
  ASSERT_EQ(names[0], "tid");
  ASSERT_EQ(vals[0], "100");

  ASSERT_TRUE(Router::get().find(Method::POST, "/users/new", names, vals));
}

TEST(RouterTest, TestPathFind3) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::POST, "/users/new", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/users/:tid", [](Context* c) {}));

  std::vector<std::string> names;
  std::vector<std::string> vals;
  names.reserve(4);
  vals.reserve(4);
  ASSERT_TRUE(Router::get().find(Method::POST, "/users/new", names, vals));
  ASSERT_TRUE(Router::get().find(Method::GET, "/users/100", names, vals));
  ASSERT_EQ(names.size(), 1);
  ASSERT_EQ(names[0], "tid");
  ASSERT_EQ(vals[0], "100");
}

TEST(RouterTest, TestPathFind4) {
  Router::get().clear();
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/ping", [](Context* c) {}));

  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::POST, "/users", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::POST, "/users/login", [](Context* c) {}));
  ASSERT_EQ(
      Router::AddPathResult::OK,
      Router::get().add(Method::POST, "/users/logout", [](Context* c) {}));

  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::POST, "/topics", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::PUT, "/topics/:tid", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/topics", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::GET, "/topics/:tid", [](Context* c) {}));

  ASSERT_EQ(
      Router::AddPathResult::OK,
      Router::get().add(Method::POST, "/topics/:tid/posts", [](Context* c) {}));
  ASSERT_EQ(Router::AddPathResult::OK,
            Router::get().add(Method::PUT, "/topics/:tid/posts/:pid",
                              [](Context* c) {}));

  std::vector<std::string> names;
  std::vector<std::string> vals;
  ASSERT_TRUE(Router::get().find(Method::GET, "/ping", names, vals));

  ASSERT_TRUE(Router::get().find(Method::POST, "/users", names, vals));
  ASSERT_TRUE(Router::get().find(Method::POST, "/users/login", names, vals));
  ASSERT_TRUE(Router::get().find(Method::POST, "/users/logout", names, vals));

  ASSERT_TRUE(Router::get().find(Method::POST, "/topics", names, vals));

  ASSERT_TRUE(Router::get().find(Method::PUT, "/topics/100", names, vals));
  ASSERT_EQ(names.size(), 1);
  ASSERT_EQ(names[0], "tid");
  ASSERT_EQ(vals[0], "100");

  ASSERT_TRUE(Router::get().find(Method::GET, "/topics", names, vals));

  names.clear();
  vals.clear();
  ASSERT_TRUE(Router::get().find(Method::GET, "/topics/200", names, vals));
  ASSERT_EQ(names.size(), 1);
  ASSERT_EQ(names[0], "tid");
  ASSERT_EQ(vals[0], "200");

  names.clear();
  vals.clear();
  ASSERT_TRUE(
      Router::get().find(Method::POST, "/topics/300/posts", names, vals));
  ASSERT_EQ(names.size(), 1);
  ASSERT_EQ(names[0], "tid");
  ASSERT_EQ(vals[0], "300");

  names.clear();
  vals.clear();
  ASSERT_TRUE(
      Router::get().find(Method::PUT, "/topics/500/posts/600", names, vals));
  ASSERT_EQ(names.size(), 2);
  ASSERT_EQ(names[0], "tid");
  ASSERT_EQ(names[1], "pid");
  ASSERT_EQ(vals[0], "500");
  ASSERT_EQ(vals[1], "600");
}

}  // namespace panda