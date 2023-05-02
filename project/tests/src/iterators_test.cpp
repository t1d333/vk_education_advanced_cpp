#include "../../include/set.h"
#include <gtest/gtest.h>

TEST(IteratorsTest, basicTest) {

  Set<std::pair<int, int>> s{{-3, 5}, {5, 5}, {-4, 1}, {-4, 4}, {0, 1}, {3, 0}};
  ASSERT_EQ(s.begin()->second, 1);
  ASSERT_EQ((++s.begin())->first, -4);
  Set<std::pair<int, int>>::iterator cur = s.end();
  Set<int> small{1};
  Set<int>::iterator it;
  it = small.begin();
  ASSERT_EQ(*it, 1);
  auto begin = s.begin();
  begin++;
  cur--;
  ASSERT_NE(begin, cur);
  while (begin != cur) {
    ++begin;
    --cur;
  }
  ASSERT_EQ(*begin, *cur);
}
