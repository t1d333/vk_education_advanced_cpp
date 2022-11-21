#include "../../include/set.h"
#include <gtest/gtest.h>

TEST(SizeTests, empty) {
  Set<int> a;
  ASSERT_EQ(a.empty(), true);
}

TEST(SizeTests, notEmpty) {
  Set<int> a;
  a.insert(10);
  ASSERT_EQ(a.empty(), false);
}

TEST(SizeTests, sizeEmpty) {
  Set<int> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(SizeTests, sizeNotEmpty) {
  Set<int> a;
  a.insert(10);
  ASSERT_EQ(a.size(), 1);
}

TEST(SizeTests, sizeCollision) {
  Set<int> a;
  a.insert(10);
  a.insert(10);
  ASSERT_EQ(a.size(), 1);
}
