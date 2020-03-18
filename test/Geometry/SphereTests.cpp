#include "Sphere.h"

#include <gtest/gtest.h>

#include <vector>

using namespace raytracer;

TEST(SphereTests, CreateSphereReturnsUniqueId) {
  geometry::Sphere s1;
  geometry::Sphere s2;
  EXPECT_TRUE(s1.id_ != s2.id_);
}

TEST(SphereTests, RayIntersectsSphereAtTwoPoints) {
  utility::Ray ray(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<double> xs = sphere.Intersect(ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(4.0, xs[0]);
  ASSERT_DOUBLE_EQ(6.0, xs[1]);
}

TEST(SphereTests, RayIntersectsSphereAtTangent) {
  utility::Ray ray(utility::Point(0, 1, -5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<double> xs = sphere.Intersect(ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(5.0, xs[0]);
  ASSERT_DOUBLE_EQ(5.0, xs[1]);
}

TEST(SphereTests, RayMissesSphere) {
  utility::Ray ray(utility::Point(0, 2, -5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<double> xs = sphere.Intersect(ray);
  ASSERT_EQ(0, xs.size());
}

TEST(SphereTests, RayOriginatesInsideSphere) {
  utility::Ray ray(utility::Point(0, 0, 0), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<double> xs = sphere.Intersect(ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-1.0, xs[0]);
  ASSERT_DOUBLE_EQ(1.0, xs[1]);
}

TEST(SphereTests, SphereIsBehindRay) {
  utility::Ray ray(utility::Point(0, 0, 5), utility::Vector(0, 0, 1));
  geometry::Sphere sphere;
  std::vector<double> xs = sphere.Intersect(ray);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-6.0, xs[0]);
  ASSERT_DOUBLE_EQ(-4.0, xs[1]);
}