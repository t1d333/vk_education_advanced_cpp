#include "../../include/set.h"
#include <gtest/gtest.h>
struct StrangeInt {
  int x;
  static int counter;
  StrangeInt() { ++counter; }
  StrangeInt(int x) : x(x) { ++counter; }
  StrangeInt(const StrangeInt &rs) : x(rs.x) { ++counter; }
  bool operator<(const StrangeInt &rs) const { return x < rs.x; }

  static void init() { counter = 0; }

  ~StrangeInt() { --counter; }

  friend std::ostream &operator<<(std::ostream &out, const StrangeInt &x) {
    out << x.x;
    return out;
  }
};
int StrangeInt::counter;

TEST(DesctructorTest, CheckOperatorLess) {
  Set<StrangeInt> s{-5, -3, -6, 13, 7, 1000, 963};
  auto it = s.lower_bound(999);
  ++it;
  ASSERT_EQ(it, s.end());
}

TEST(DesctructorTest, basicTest) {

  StrangeInt::init();
  {
    Set<StrangeInt> s{5, 4, 3, 2, 1, 0};
    ASSERT_EQ(s.size(), 6);
  }
  ASSERT_FALSE(StrangeInt::counter);
  {
    Set<StrangeInt> s{-3, 3, -2, 2, -1, 1};
    Set<StrangeInt> s1(s);
    s1.insert(0);
    Set<StrangeInt> s2(s1);
    ASSERT_NE(s1.find(0), s1.end());
    s1 = s;
    ASSERT_EQ(s1.find(0), s1.end());
  }
  ASSERT_FALSE(StrangeInt::counter);
}
