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
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  geometry::Sphere s;
  std::vector<geometry::Intersection> xs = geometry::Intersect(s, r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(4.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(6.0, xs[1].t_);
}

TEST(SphereTests, RayIntersectsSphereAtTangent) {
  utility::Ray r(utility::Point(0, 1, -5), utility::Vector(0, 0, 1));
  geometry::Sphere s;
  std::vector<geometry::Intersection> xs = geometry::Intersect(s, r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(5.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(5.0, xs[1].t_);
}

TEST(SphereTests, RayMissesSphere) {
  utility::Ray r(utility::Point(0, 2, -5), utility::Vector(0, 0, 1));
  geometry::Sphere s;
  std::vector<geometry::Intersection> xs = geometry::Intersect(s, r);
  ASSERT_EQ(0, xs.size());
}

TEST(SphereTests, RayOriginatesInsideSphere) {
  utility::Ray r(utility::Point(0, 0, 0), utility::Vector(0, 0, 1));
  geometry::Sphere s;
  std::vector<geometry::Intersection> xs = geometry::Intersect(s, r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-1.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(1.0, xs[1].t_);
}

TEST(SphereTests, SphereIsBehindRay) {
  utility::Ray r(utility::Point(0, 0, 5), utility::Vector(0, 0, 1));
  geometry::Sphere s;
  std::vector<geometry::Intersection> xs = geometry::Intersect(s, r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-6.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(-4.0, xs[1].t_);
}

TEST(SphereTests, DefaultTransformationOfSphere) {
  geometry::Sphere s;
  EXPECT_TRUE(utility::Identity() == s.transform_);
}

TEST(SphereTests, ChangeTransformationOfSphere) {
  geometry::Sphere s;
  utility::Translation t(2, 3, 4);
  s.SetTransform(t);
  EXPECT_TRUE(t == s.transform_);
}

TEST(SphereTests, IntersectScaledSphereWithRay) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  geometry::Sphere s;
  s.SetTransform(utility::Scaling(2, 2, 2));
  std::vector<geometry::Intersection> xs = geometry::Intersect(s, r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(3, xs[0].t_);
  ASSERT_DOUBLE_EQ(7, xs[1].t_);
}

TEST(SphereTests, IntersectTranslatedSphereWithRay) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  geometry::Sphere s;
  s.SetTransform(utility::Translation(5, 0, 0));
  std::vector<geometry::Intersection> xs = geometry::Intersect(s, r);
  ASSERT_EQ(0, xs.size());
}