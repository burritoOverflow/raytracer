#include "Triangle.hpp"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

class TriangleTest : public ::testing::Test {
protected:
  void SetUp() override {
    triangle = std::make_shared<geometry::Triangle>(
        Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  }

  std::shared_ptr<geometry::Triangle> triangle;
};

TEST_F(TriangleTest, ConstructingATriangle) {
  auto p1 = Point(0, 1, 0);
  auto p2 = Point(-1, 0, 0);
  auto p3 = Point(1, 0, 0);

  EXPECT_TRUE(p1 == triangle->p1_);
  EXPECT_TRUE(p2 == triangle->p2_);
  EXPECT_TRUE(p3 == triangle->p3_);
  EXPECT_TRUE(Vector(-1, -1, 0) == triangle->e1_);
  EXPECT_TRUE(Vector(1, -1, 0) == triangle->e2_);
  EXPECT_TRUE(Vector(0, 0, -1) == triangle->normal_);
}

TEST_F(TriangleTest, FindingTheNormalOnATriangle) {
  auto n1 = triangle->LocalNormalAt(Point(0, 0.5, 0));
  auto n2 = triangle->LocalNormalAt(Point(-0.5, 0.75, 0));
  auto n3 = triangle->LocalNormalAt(Point(0.5, 0.25, 0));
  EXPECT_TRUE(n1 == triangle->normal_);
  EXPECT_TRUE(n2 == triangle->normal_);
  EXPECT_TRUE(n3 == triangle->normal_);
}

TEST_F(TriangleTest, IntersectingARayParallelToTheTriangle) {
  auto ray = Ray(Point(0, -1, -2), Vector(0, 1, 0));

  auto xs = triangle->LocalIntersect(ray);
  EXPECT_TRUE(xs.empty());
}

TEST_F(TriangleTest, ARayMissesTheP1P3Edge) {
  auto ray = Ray(Point(0, -1, -2), Vector(0, 1, 0));

  auto xs = triangle->LocalIntersect(ray);
  EXPECT_TRUE(xs.empty());
}

TEST_F(TriangleTest, ARayMissesTheP1P2Edge) {
  auto ray = Ray(Point(-1, 1, -2), Vector(0, 0, 1));

  auto xs = triangle->LocalIntersect(ray);
  EXPECT_TRUE(xs.empty());
}

TEST_F(TriangleTest, ARayMissesTheP2P3Edge) {
  auto ray = Ray(Point(0, -1, -2), Vector(0, 0, 1));

  auto xs = triangle->LocalIntersect(ray);
  EXPECT_TRUE(xs.empty());
}

TEST_F(TriangleTest, ARayStrikesATriangle) {
  auto ray = Ray(Point(0, 0.5, -2), Vector(0, 0, 1));

  auto xs = triangle->LocalIntersect(ray);
  EXPECT_EQ(1, xs.size());
  EXPECT_EQ(2, xs[0].t_);
}
