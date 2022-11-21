#include "../../include/set.h"
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

TEST(ConstructorsTest, empty) {
  Set<int> *a = new Set<int>();
  ASSERT_NE(a, nullptr);
  ASSERT_EQ(a->empty(), true);
  delete a;
}

TEST(ConstructorsTest, initializer_list) {
  Set<int> a{1, 2, 3, 4};
  ASSERT_EQ(a.size(), 4);
  std::vector<int> buf;
  a.getData(buf);
  for (size_t i = 1; i < 5; i++) {
    ASSERT_EQ(i, buf[i - 1]);
  }
}

TEST(ConstructorsTest, copyConsturctor) {
  Set<int> a{1, 2, 3, 4};
  Set<int> b(a);
  ASSERT_EQ(b.size(), 4);
  std::vector<int> buf;
  b.getData(buf);
  for (size_t i = 1; i < 5; i++) {
    ASSERT_EQ(i, buf[i - 1]);
  }
}
