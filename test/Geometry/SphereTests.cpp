#include "Sphere.h"

#include <gtest/gtest.h>

#include <vector>

#include "Intersection.h"

using namespace raytracer;

TEST(SphereTests, CreateSphereReturnsUniqueId) {
  geometry::Sphere s1;
  geometry::Sphere s2;
  EXPECT_TRUE(s1.id_ != s2.id_);
}

TEST(SphereTests, RayIntersectsSphereAtTwoPoints) {
  utility::Ray ray(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<geometry::Intersection> xs = geometry::Intersect(sphere, ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(4.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(6.0, xs[1].t_);
}

TEST(SphereTests, RayIntersectsSphereAtTangent) {
  utility::Ray ray(utility::Point(0, 1, -5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<geometry::Intersection> xs = geometry::Intersect(sphere, ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(5.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(5.0, xs[1].t_);
}

TEST(SphereTests, RayMissesSphere) {
  utility::Ray ray(utility::Point(0, 2, -5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<geometry::Intersection> xs = geometry::Intersect(sphere, ray);
  ASSERT_EQ(0, xs.size());
}

TEST(SphereTests, RayOriginatesInsideSphere) {
  utility::Ray ray(utility::Point(0, 0, 0), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<geometry::Intersection> xs = geometry::Intersect(sphere, ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-1.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(1.0, xs[1].t_);
}

TEST(SphereTests, SphereIsBehindRay) {
  utility::Ray ray(utility::Point(0, 0, 5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<geometry::Intersection> xs = geometry::Intersect(sphere, ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-6.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(-4.0, xs[1].t_);
}
