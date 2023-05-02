#include "../../include/set.h"
#include <gtest/gtest.h>

TEST(ConstnessTest, basicTest) {
  const Set<int> s{-4, 5, 3, 0, 7};
  ASSERT_NE(s.find(3), s.end());
  ASSERT_EQ(*s.lower_bound(2), 3);
  ASSERT_EQ(s.lower_bound(8), s.end());
  ASSERT_EQ(*s.lower_bound(-2), 0);
  ASSERT_FALSE(s.empty());
  ASSERT_EQ(s.size(), 5);
  auto first = s.begin();
  Set<int>::iterator last = s.end();
  ASSERT_EQ(*first, -4);
  ASSERT_EQ(*(--last), 7);
}
