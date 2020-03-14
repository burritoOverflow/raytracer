#include <gtest/gtest.h>

#include "Point.h"

TEST(PointTests, PointCreatesAPointTuple) {
  raytracer::Tuple a(4, -4, 3, 1);
  raytracer::Point p(4, -4, 3);

  for (int i = 0; i < 4; ++i) {
    ASSERT_DOUBLE_EQ(a[i], p[i]) << "The point and tuple differ at index " << i;
  }
}