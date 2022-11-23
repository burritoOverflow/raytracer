#include "Point.hpp"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(PointTests, PointCreatesAPointTuple) {
  Tuple a(4, -4, 3, 1);
  Point p(4, -4, 3);

  for (int i = 0; i < 4; ++i) {
    ASSERT_DOUBLE_EQ(a[i], p[i]) << "The point and tuple differ at index " << i;
  }
}
