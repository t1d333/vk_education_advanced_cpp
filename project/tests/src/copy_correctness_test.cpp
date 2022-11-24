#include "../../include/set.h"
#include <gtest/gtest.h>

TEST(CopyCorrectnessTest, basicTest) {

  int elems[] = {3, 3, -1, 6, 0, 0, 17, -5, 4, 2};
  Set<int> s1(elems, elems + 10);
  std::set<int> set_elems(elems, elems + 10);
  Set<int> s2 = s1;
  s2.insert(5);
  s2.insert(18);
  s2.insert(-2);
  auto s1_it = s1.begin(), s2_it = s2.begin();
  auto s_it = set_elems.begin();
  while (s1_it != s1.end() || s2_it != s2.end() || s_it != set_elems.end()) {
    if (*s2_it == 5 || *s2_it == 18 || *s2_it == -2) {
      ++s2_it;
      continue;
    }
    ASSERT_EQ(*s1_it, *s2_it);
    ASSERT_EQ(*s1_it, *s_it);
    ASSERT_EQ(*s2_it, *s_it);
    ++s1_it, ++s2_it, ++s_it;
  }

  s1 = s2;
  s2.insert(19);
  auto cur_end = s2.end();
  cur_end--;
  s1_it = s1.begin(), s2_it = s2.begin();
  while (s1_it != s1.end() || s2_it != cur_end) {
    ASSERT_EQ(*s1_it, *s2_it);
    ++s1_it, ++s2_it;
  }

  s1 = s1 = s2;
  s1_it = s1.begin(), s2_it = s2.begin();
  while (s1_it != s1.end() || s2_it != s2.end()) {
    ASSERT_EQ(*s1_it, *s2_it);
    ++s1_it, ++s2_it;
  }
}
