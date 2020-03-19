#include "Intersection.h"

#include <gtest/gtest.h>

#include "Ray.h"
#include "Sphere.h"

using namespace raytracer;

TEST(IntersectionTests, IntersectionEncapsulatesTAndObject) {
  geometry::Sphere sphere;
  geometry::Intersection intersection(3.5, sphere);
  ASSERT_DOUBLE_EQ(3.5, intersection.t_);
  EXPECT_TRUE(sphere == intersection.object_);
}

TEST(IntersectionTests, AggregatingIntersections) {
  geometry::Sphere sphere;
  geometry::Intersection i1(1, sphere);
  geometry::Intersection i2(2, sphere);
  std::vector<geometry::Intersection> xs = geometry::Intersections({i1, i2});
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(1, xs[0].t_);
  ASSERT_DOUBLE_EQ(2, xs[1].t_);
}

TEST(IntersectionTests, IntersectSetsTheObjectOnTheIntersection) {
  utility::Ray ray(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<geometry::Intersection> xs = geometry::Intersect(sphere, ray);
  ASSERT_EQ(2, xs.size());
  EXPECT_TRUE(sphere == xs[0].object_);
  EXPECT_TRUE(sphere == xs[1].object_);
}