#include "Cone.h"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(ConeTest, IntersectingAConeWithARay) {
  struct Example {
    utility::Point origin;
    utility::Vector direction;
    double t0;
    double t1;
  };
  std::vector<Example> examples{
      {utility::Point(0, 0, -5), utility::Vector(0, 0, 1), 5, 5},
      {utility::Point(0, 0, -5), utility::Vector(1, 1, 1), 8.6602540378443855,
       8.6602540378443855},
      {utility::Point(1, 1, -5), utility::Vector(-0.5, -1, 1),
       4.5500556793563494, 49.449944320643645},
  };

  auto cone = std::make_unique<geometry::Cone>();
  for (auto &example : examples) {
    auto direction = example.direction.Normalize();
    auto ray = utility::Ray(example.origin, direction);
    auto xs = cone->LocalIntersect(ray);
    EXPECT_EQ(2, xs.size());
    EXPECT_DOUBLE_EQ(example.t0, xs[0].t_);
    EXPECT_DOUBLE_EQ(example.t1, xs[1].t_);
  }
}

TEST(ConeTest, IntersectingAConeWithARayParallelToOneOfItsHalves) {
  auto cone = std::make_unique<geometry::Cone>();
  auto direction = utility::Vector(0, 1, 1).Normalize();
  auto ray = utility::Ray(utility::Point(0, 0, -1), direction);
  auto xs = cone->LocalIntersect(ray);
  EXPECT_EQ(1, xs.size());
  EXPECT_DOUBLE_EQ(0.35355339059327379, xs[0].t_);
}

TEST(ConeTest, IntersectingAConeEndCaps) {
  struct Example {
    utility::Point origin;
    utility::Vector direction;
    size_t count;
  };
  std::vector<Example> examples{
      {utility::Point(0, 0, -5), utility::Vector(0, 1, 0), 0},
      {utility::Point(0, 0, -0.25), utility::Vector(0, 1, 1), 2},
      {utility::Point(0, 0, -0.25), utility::Vector(0, 1, 0), 4},
  };

  auto cone = std::make_unique<geometry::Cone>();
  cone->minimum_ = -0.5;
  cone->maximum_ = 0.5;
  cone->closed_ = true;
  for (auto &example : examples) {
    auto direction = example.direction.Normalize();
    auto ray = utility::Ray(example.origin, direction);
    auto xs = cone->LocalIntersect(ray);
    EXPECT_EQ(example.count, xs.size());
  }
}

TEST(ConeTest, ComputingTheNormalVectorOnACone) {
  struct Example {
    utility::Point point;
    utility::Vector normal;
  };
  std::vector<Example> examples{
      {utility::Point(0, 0, 0), utility::Vector(0, 0, 0)},
      {utility::Point(1, 1, 1), utility::Vector(1, -std::sqrt(2), 1)},
      {utility::Point(-1, -1, 0), utility::Vector(-1, 1, 0)},
  };

  auto cone = std::make_unique<geometry::Cone>();
  for (auto &example : examples) {
    auto normal = cone->LocalNormalAt(example.point);
    EXPECT_TRUE(example.normal == normal);
  }
}