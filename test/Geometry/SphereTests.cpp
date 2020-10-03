#include "Sphere.h"

#include <gtest/gtest.h>

#include <vector>

#include "Intersection.h"

using namespace raytracer;

TEST(SphereTest, CreateSphereReturnsUniqueId) {
  auto s1 = std::make_shared<geometry::Sphere>();
  auto s2 = std::make_shared<geometry::Sphere>();
  EXPECT_TRUE(s1->id_ != s2->id_);
}

TEST(SphereTest, RayIntersectsSphereAtTwoPoints) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(4.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(6.0, xs[1].t_);
}

TEST(SphereTest, RayIntersectsSphereAtTangent) {
  utility::Ray r(utility::Point(0, 1, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(5.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(5.0, xs[1].t_);
}

TEST(SphereTest, RayMissesSphere) {
  utility::Ray r(utility::Point(0, 2, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(0, xs.size());
}

TEST(SphereTest, RayOriginatesInsideSphere) {
  utility::Ray r(utility::Point(0, 0, 0), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-1.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(1.0, xs[1].t_);
}

TEST(SphereTest, SphereIsBehindRay) {
  utility::Ray r(utility::Point(0, 0, 5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = s->Intersect(r);
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(-6.0, xs[0].t_);
  ASSERT_DOUBLE_EQ(-4.0, xs[1].t_);
}

TEST(SphereTest, NormalOnSphereAtPointOnXAxis) {
  geometry::Sphere s;
  utility::Vector n = s.NormalAt(utility::Point(1, 0, 0));
  EXPECT_TRUE(utility::Vector(1, 0, 0) == n);
}

TEST(SphereTest, NormalOnSphereAtPointOnYAxis) {
  geometry::Sphere s;
  utility::Vector n = s.NormalAt(utility::Point(0, 1, 0));
  EXPECT_TRUE(utility::Vector(0, 1, 0) == n);
}

TEST(SphereTest, NormalOnSphereAtPointOnZAxis) {
  geometry::Sphere s;
  utility::Vector n = s.NormalAt(utility::Point(0, 0, 1));
  EXPECT_TRUE(utility::Vector(0, 0, 1) == n);
}

TEST(SphereTest, NormalOnSphereAtNonaxialPoint) {
  geometry::Sphere s;
  utility::Vector n =
      s.NormalAt(utility::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  EXPECT_TRUE(utility::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3) == n);
}

TEST(SphereTest, NormalIsNormalizedVector) {
  geometry::Sphere s;
  utility::Vector n =
      s.NormalAt(utility::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  EXPECT_TRUE(n == n.Normalize());
}

TEST(SphereTest, AHelperForProducingASphereWithAGlassyMaterial) {
  geometry::Sphere s = geometry::GlassSphere();
  EXPECT_TRUE(utility::Identity() == s.transform_);
  ASSERT_DOUBLE_EQ(1.0, s.material_.transparency_);
  ASSERT_DOUBLE_EQ(1.5, s.material_.refractive_index_);
}
