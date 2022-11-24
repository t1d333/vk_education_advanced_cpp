#include "../../include/set.h"
#include <gtest/gtest.h>
TEST(EraseTest, basicTest) {

  Set<std::string> s{"abacaba", "hello", "p"};
  s.erase("miss");
  s.erase("hello");
  ASSERT_EQ(s.size(), 2);
  s.erase("p");

  ASSERT_EQ(*s.begin(), "abacaba");
  s.erase("1");
  s.erase("abacaba");
  s.erase("012");
  ASSERT_TRUE(s.empty());
}
