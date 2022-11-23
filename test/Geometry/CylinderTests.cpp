#include "Cylinder.hpp"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(CylinderTest, ARayMissesACylinder) {
  struct Example {
    utility::Point origin;
    utility::Vector direction;
  };
  std::vector<Example> examples{
      {utility::Point(1, 0, 0), utility::Vector(0, 1, 0)},
      {utility::Point(0, 0, 0), utility::Vector(0, 1, 0)},
      {utility::Point(0, 0, -5), utility::Vector(1, 1, 1)},
  };

  auto cylinder = std::make_unique<geometry::Cylinder>();
  for (auto &example : examples) {
    auto direction = example.direction.Normalize();
    auto ray = utility::Ray(example.origin, direction);
    auto xs = cylinder->LocalIntersect(ray);
    EXPECT_EQ(0, xs.size());
  }
}

TEST(CylinderTest, ARayStrikesACylinder) {
  struct Example {
    utility::Point origin;
    utility::Vector direction;
    double t0;
    double t1;
  };
  std::vector<Example> examples{
      {utility::Point(1, 0, -5), utility::Vector(0, 0, 1), 5, 5},
      {utility::Point(0, 0, -5), utility::Vector(0, 0, 1), 4, 6},
      {utility::Point(0.5, 0, -5), utility::Vector(0.1, 1, 1),
       6.8079819170273197, 7.0887234393788612}};

  auto cylinder = std::make_unique<geometry::Cylinder>();
  for (auto &example : examples) {
    auto direction = example.direction.Normalize();
    auto ray = utility::Ray(example.origin, direction);
    auto xs = cylinder->LocalIntersect(ray);
    EXPECT_EQ(2, xs.size());
    EXPECT_DOUBLE_EQ(example.t0, xs[0].t_);
    EXPECT_DOUBLE_EQ(example.t1, xs[1].t_);
  }
}

TEST(CylinderTest, NormalVectorOnACylinder) {
  struct Example {
    utility::Point point;
    utility::Vector normal;
  };
  std::vector<Example> examples{
      {utility::Point(1, 0, 0), utility::Vector(1, 0, 0)},
      {utility::Point(0, 5, -1), utility::Vector(0, 0, -1)},
      {utility::Point(0, -2, 1), utility::Vector(0, 0, 1)},
      {utility::Point(-1, 1, 0), utility::Vector(-1, 0, 0)}};

  auto cylinder = std::make_unique<geometry::Cylinder>();
  for (auto &example : examples) {
    auto normal = cylinder->LocalNormalAt(example.point);
    EXPECT_TRUE(example.normal == normal);
  }
}

TEST(CylinderTest, TheDefaultMinimumAndMaximumForACylinder) {
  auto cylinder = std::make_unique<geometry::Cylinder>();
  EXPECT_DOUBLE_EQ(-std::numeric_limits<double>::infinity(),
                   cylinder->minimum_);
}

TEST(CylinderTest, IntersectingAConstrainedCylinder) {
  struct Example {
    utility::Point point;
    utility::Vector direction;
    size_t count;
  };
  std::vector<Example> examples{
      {utility::Point(0, 1.5, 0), utility::Vector(0.1, 1, 0), 0},
      {utility::Point(0, 3, -5), utility::Vector(0, 0, 1), 0},
      {utility::Point(0, 0, -5), utility::Vector(0, 0, 1), 0},
      {utility::Point(0, 2, -5), utility::Vector(0, 0, 1), 0},
      {utility::Point(0, 1, -5), utility::Vector(0, 0, 1), 0},
      {utility::Point(0, 1.5, -2), utility::Vector(0, 0, 1), 2}};

  auto cylinder = std::make_unique<geometry::Cylinder>();
  cylinder->minimum_ = 1;
  cylinder->maximum_ = 2;
  for (auto &example : examples) {
    auto direction = example.direction.Normalize();
    auto ray = Ray(example.point, direction);
    auto xs = cylinder->LocalIntersect(ray);
    EXPECT_EQ(example.count, xs.size());
  }
}

TEST(CylinderTest, TheDefaultClosedValueForACylinder) {
  auto cylinder = std::make_unique<geometry::Cylinder>();
  EXPECT_FALSE(cylinder->closed_);
}

TEST(CylinderTest, IntersectingTheCapsOfAClosedCylinder) {
  struct Example {
    utility::Point point;
    utility::Vector direction;
    size_t count;
  };
  std::vector<Example> examples{
      {utility::Point(0, 3, 0), utility::Vector(0, -1, 0), 2},
      {utility::Point(0, 3, -2), utility::Vector(0, -1, 2), 2},
      {utility::Point(0, 4, -2), utility::Vector(0, -1, 1), 2}, // corner case
      {utility::Point(0, 0, -2), utility::Vector(0, 1, 2), 2},
      {utility::Point(0, -1, -2), utility::Vector(0, 1, 1), 2} // corner case
  };

  auto cylinder = std::make_unique<geometry::Cylinder>();
  cylinder->minimum_ = 1;
  cylinder->maximum_ = 2;
  cylinder->closed_ = true;
  for (auto &example : examples) {
    auto direction = example.direction.Normalize();
    auto ray = Ray(example.point, direction);
    auto xs = cylinder->LocalIntersect(ray);
    EXPECT_EQ(example.count, xs.size());
  }
}

TEST(CylinderTest, TheNormalVectorOnACylinderEndCaps) {
  struct Example {
    utility::Point point;
    utility::Vector normal;
  };
  std::vector<Example> examples{
      {utility::Point(0, 1, 0), utility::Vector(0, -1, 0)},
      {utility::Point(0.5, 1, 0), utility::Vector(0, -1, 0)},
      {utility::Point(0, 1, 0.5), utility::Vector(0, -1, 0)},
      {utility::Point(0, 2, 0), utility::Vector(0, 1, 0)},
      {utility::Point(0.5, 2, 0), utility::Vector(0, 1, 0)},
      {utility::Point(0, 2, 0.5), utility::Vector(0, 1, 0)},
  };

  auto cylinder = std::make_unique<geometry::Cylinder>();
  cylinder->minimum_ = 1;
  cylinder->maximum_ = 2;
  cylinder->closed_ = true;
  for (auto &example : examples) {
    auto normal = cylinder->LocalNormalAt(example.point);
    EXPECT_TRUE(example.normal == normal);
  }
}