#include "Ray.hpp"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(RayTests, CreateAndQueryRay) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  EXPECT_TRUE(origin == r.origin_);
  EXPECT_TRUE(direction == r.direction_);
}

TEST(RayTests, ComputePointFromDistance) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  EXPECT_TRUE(Point(2, 3, 4) == r.Position(0));
  EXPECT_TRUE(Point(3, 3, 4) == r.Position(1));
  EXPECT_TRUE(Point(1, 3, 4) == r.Position(-1));
  EXPECT_TRUE(Point(4.5, 3, 4) == r.Position(2.5));
}

TEST(RayTests, TranslateRay) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Translation m(3, 4, 5);
  Ray r2 = Transform(r, m);
  EXPECT_TRUE(Point(4, 6, 8) == r2.origin_);
  EXPECT_TRUE(Vector(0, 1, 0) == r2.direction_);
}

TEST(Ray, ScaleRay) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Scaling m(2, 3, 4);
  Ray r2 = m * r;
  EXPECT_TRUE(Point(2, 6, 12) == r2.origin_);
  EXPECT_TRUE(Vector(0, 3, 0) == r2.direction_);
}
