#include "Plane.hpp"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(PlaneTest, TheNormalOfAPlaneIsConstantEverywhere) {
  auto plane = std::make_shared<geometry::Plane>();
  Point p1 = Point(0, 0, 0);
  Point p2 = Point(10, 0, -10);
  Point p3 = Point(-5, 0, 150);
  Vector n1 = plane->LocalNormalAt(p1);
  Vector n2 = plane->LocalNormalAt(p2);
  Vector n3 = plane->LocalNormalAt(p3);
  EXPECT_TRUE(Vector(0, 1, 0) == n1);
  EXPECT_TRUE(Vector(0, 1, 0) == n2);
  EXPECT_TRUE(Vector(0, 1, 0) == n3);
}

TEST(PlaneTest, IntersectWithARayParallelToThePlane) {
  auto p = std::make_shared<geometry::Plane>();
  Ray r(Point(0, 10, 0), Vector(0, 0, 1));
  auto xs = p->LocalIntersect(r);
  ASSERT_EQ(0, xs.size());
}

TEST(PlaneTest, IntersectWithACoplanarRay) {
  auto p = std::make_shared<geometry::Plane>();
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  auto xs = p->LocalIntersect(r);
  ASSERT_EQ(0, xs.size());
}

TEST(PlaneTest, ARayIntersectingAPlaneFromAbove) {
  auto p = std::make_shared<geometry::Plane>();
  Ray r(Point(0, 1, 0), Vector(0, -1, 0));
  auto xs = p->LocalIntersect(r);
  ASSERT_EQ(1, xs.size());
  ASSERT_DOUBLE_EQ(1, xs[0].t_);
  EXPECT_TRUE(*p == *xs[0].object_);
}

TEST(PlaneTest, ARayIntersectingAPlaneFromBelow) {
  auto p = std::make_shared<geometry::Plane>();
  Ray r(Point(0, -1, 0), Vector(0, 1, 0));
  auto xs = p->LocalIntersect(r);
  ASSERT_EQ(1, xs.size());
  ASSERT_DOUBLE_EQ(1, xs[0].t_);
  EXPECT_TRUE(*p == *xs[0].object_);
}
