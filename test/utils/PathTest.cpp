#include <gtest/gtest.h>
#include <panda/utils/Path.h>

namespace panda {
namespace utils {

TEST(PathTest, TestCanonicalize0) {
  std::string s("hello/");
  canonicalizePath(s);
  ASSERT_EQ(s, "/hello");
}

TEST(PathTest, TestCanonicalize1) {
  std::string s("/hello/");
  canonicalizePath(s);
  ASSERT_EQ(s, "/hello");
}

TEST(PathTest, TestCanonicalize2) {
  std::string s("///hello/////world");
  canonicalizePath(s);
  ASSERT_EQ(s, "/hello/world");
}

TEST(PathTest, TestCanonicalize3) {
  std::string s("/hello/////world");
  canonicalizePath(s);
  ASSERT_EQ(s, "/hello/world");
}

TEST(PathTest, TestCanonicalize4) {
  std::string s("///hello/////world");
  canonicalizePath(s);
  ASSERT_EQ(s, "/hello/world");
}

TEST(PathTest, TestCanonicalize5) {
  std::string s("//");
  canonicalizePath(s);
  ASSERT_EQ(s, "/");
}

TEST(PathTest, TestCanonicalize6) {
  std::string s("////");
  canonicalizePath(s);
  ASSERT_EQ(s, "/");
}

}  // namespace utils
}  // namespace panda