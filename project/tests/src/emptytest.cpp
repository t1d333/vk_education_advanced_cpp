#include "../../include/set.h"
#include <gtest/gtest.h>

TEST(EmptyTest, basicTest) {
  Set<std::string> s;
  ASSERT_TRUE(s.empty());
  auto begin = s.begin(), end = s.end();
  ASSERT_EQ(begin, end);
  std::string elem("abacaba");
  s.insert(elem);
  ASSERT_EQ(*s.lower_bound("aac"), elem);
  Set<std::string> empty;
  Set<std::string> s2{"opa"};
  s2 = empty;
  ASSERT_FALSE(s2.size());
  Set<std::string> s3(s2);
  ASSERT_TRUE(s3.empty());
}
