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

TEST(RayTests, ComputePointFromDistance) {
  utility::Ray r(utility::Point(2, 3, 4), utility::Vector(1, 0, 0));
  EXPECT_TRUE(utility::Point(2, 3, 4) == r.Position(0));
  EXPECT_TRUE(utility::Point(3, 3, 4) == r.Position(1));
  EXPECT_TRUE(utility::Point(1, 3, 4) == r.Position(-1));
  EXPECT_TRUE(utility::Point(4.5, 3, 4) == r.Position(2.5));
}

TEST(RayTests, TranslateRay) {
  utility::Ray r(utility::Point(1, 2, 3), utility::Vector(0, 1, 0));
  utility::Translation m(3, 4, 5);
  utility::Ray r2 = utility::Transform(r, m);
  EXPECT_TRUE(utility::Point(4, 6, 8) == r2.origin_);
  EXPECT_TRUE(utility::Vector(0, 1, 0) == r2.direction_);
}

TEST(Ray, ScaleRay) {
  utility::Ray r(utility::Point(1, 2, 3), utility::Vector(0, 1, 0));
  utility::Scaling m(2, 3, 4);
  utility::Ray r2 = m * r;
  EXPECT_TRUE(utility::Point(2, 6, 12) == r2.origin_);
  EXPECT_TRUE(utility::Vector(0, 3, 0) == r2.direction_);
}
