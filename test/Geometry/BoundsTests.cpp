#include "Bounds.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(BoundsTest, MergingTwoBoundsYieldsTheBiggestBoundingBox) {
  auto bounds1 = geometry::Bounds(Point(-1, 0, -1), Point(1, 0, 1));
  auto bounds2 =
      geometry::Bounds(Point(-std::numeric_limits<double>::infinity(), -1, 0),
                       Point(std::numeric_limits<double>::infinity(), 1, 0));

  bounds1.Merge(bounds2);
  EXPECT_TRUE(
      geometry::Bounds(Point(-std::numeric_limits<double>::infinity(), -1, -1),
                       Point(std::numeric_limits<double>::infinity(), 1, 1)) ==
      bounds1);
}

TEST(BoundsTest, RotationBy45DegreesYieldsUpdatedBounds) {
  auto bounds = geometry::Bounds(Point(-1, -1, -1), Point(1, 1, 1));
  RotationY r = RotationY(M_PI_4);
  bounds.Transform(r);

  EXPECT_TRUE(geometry::Bounds(Point(-sqrt(2), -1, -sqrt(2)),
                               Point(sqrt(2), 1, sqrt(2))) == bounds);
}
