#include "Point.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(PointTests, PointCreatesAPointTuple) {
  utility::Tuple a(4, -4, 3, 1);
  utility::Point p(4, -4, 3);

  for (int i = 0; i < 4; ++i) {
    ASSERT_DOUBLE_EQ(a[i], p[i]) << "The point and tuple differ at index " << i;
  }
}
