#include "Ray.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(RayTests, CreateAndQueryRay) {
  utility::Point origin(1, 2, 3);
  utility::Vector direction(4, 5, 6);
  utility::Ray r(origin, direction);
  EXPECT_TRUE(origin == r.origin_);
  EXPECT_TRUE(direction == r.direction_);
}

TEST(RayTests, ComputPointFromDistance) {
  utility::Ray r(utility::Point(2, 3, 4), utility::Vector(1, 0, 0));
  EXPECT_TRUE(utility::Point(2, 3, 4) == r.Position(0));
  EXPECT_TRUE(utility::Point(3, 3, 4) == r.Position(1));
  EXPECT_TRUE(utility::Point(1, 3, 4) == r.Position(-1));
  EXPECT_TRUE(utility::Point(4.5, 3, 4) == r.Position(2.5));
}
