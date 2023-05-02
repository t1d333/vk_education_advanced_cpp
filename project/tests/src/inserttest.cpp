#include "../../include/set.h"
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

TEST(InsertTest, base) {
  Set<int> a;
  a.insert(10);
  std::vector<int> buf;
  a.getData(buf);
  ASSERT_EQ(buf[0], 10);
}

TEST(InsertTest, collision) {
  Set<int> a;
  a.insert(10);
  a.insert(10);
  ASSERT_EQ(a.size(), 1);
  std::vector<int> buf;
  a.getData(buf);
  ASSERT_EQ(buf[0], 10);
}
