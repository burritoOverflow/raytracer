#include "Sphere.h"

#include <gtest/gtest.h>

#include <vector>

#include "Intersection.h"

using namespace raytracer;

TEST(SphereTests, CreateSphereReturnsUniqueId) {
  auto s1 = std::make_shared<geometry::Sphere>();
  auto s2 = std::make_shared<geometry::Sphere>();
  EXPECT_TRUE(s1->id_ != s2->id_);
}

TEST(SphereTests, RayIntersectsSphereAtTwoPoints) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(4.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(6.0, xs[1].t_);
}

TEST(SphereTests, RayIntersectsSphereAtTangent) {
  utility::Ray r(utility::Point(0, 1, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(5.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(5.0, xs[1].t_);
}

TEST(SphereTests, RayMissesSphere) {
  utility::Ray r(utility::Point(0, 2, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(0, xs.size());
}

TEST(SphereTests, RayOriginatesInsideSphere) {
  utility::Ray r(utility::Point(0, 0, 0), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-1.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(1.0, xs[1].t_);
}

TEST(SphereTests, SphereIsBehindRay) {
  utility::Ray r(utility::Point(0, 0, 5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-6.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(-4.0, xs[1].t_);
}

TEST(SphereTests, NormalOnSphereAtPointOnXAxis) {
  geometry::Sphere s;
  utility::Vector n = s.NormalAt(utility::Point(1, 0, 0));
  EXPECT_TRUE(utility::Vector(1, 0, 0) == n);
}

TEST(SphereTests, NormalOnSphereAtPointOnYAxis) {
  geometry::Sphere s;
  utility::Vector n = s.NormalAt(utility::Point(0, 1, 0));
  EXPECT_TRUE(utility::Vector(0, 1, 0) == n);
}

TEST(SphereTests, NormalOnSphereAtPointOnZAxis) {
  geometry::Sphere s;
  utility::Vector n = s.NormalAt(utility::Point(0, 0, 1));
  EXPECT_TRUE(utility::Vector(0, 0, 1) == n);
}

TEST(SphereTests, NormalOnSphereAtNonaxialPoint) {
  geometry::Sphere s;
  utility::Vector n =
      s.NormalAt(utility::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  EXPECT_TRUE(utility::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3) == n);
}

TEST(SphereTests, NormalIsNormalizedVector) {
  geometry::Sphere s;
  utility::Vector n =
      s.NormalAt(utility::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  EXPECT_TRUE(n == n.Normalize());
}
