#include "Cube.h"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(CubeTest, ARayIntersectsACube) {
  struct Example {
    utility::Point origin;
    utility::Vector direction;
    double t0;
    double t1;
  };
  std::vector<Example> examples{
      {utility::Point(5, 0.5, 0), utility::Vector(-1, 0, 0), 4, 6},
      {utility::Point(-5, 0.5, 0), utility::Vector(1, 0, 0), 4, 6},
      {utility::Point(0.5, 5, 0), utility::Vector(0, -1, 0), 4, 6},
      {utility::Point(0.5, -5, 0), utility::Vector(0, 1, 0), 4, 6},
      {utility::Point(0.5, 0, 5), utility::Vector(0, 0, -1), 4, 6},
      {utility::Point(0.5, 0, -5), utility::Vector(0, 0, 1), 4, 6},
      {utility::Point(0, 0.5, 0), utility::Vector(0, 0, 1), -1, 1},
  };

  for (auto &example : examples) {
    auto cube = std::make_unique<geometry::Cube>();
    auto ray = utility::Ray(example.origin, example.direction);
    auto xs = cube->LocalIntersect(ray);
    EXPECT_EQ(2, xs.size());
    EXPECT_DOUBLE_EQ(example.t0, xs[0].t_);
    EXPECT_DOUBLE_EQ(example.t1, xs[1].t_);
  }
}

TEST(CubeTest, ARayMissesACube) {
  struct Example {
    utility::Point origin;
    utility::Vector direction;
  };
  std::vector<Example> examples{
      {utility::Point(-2, 0, 0), utility::Vector(0.2673, 0.5346, 0.8018)},
      {utility::Point(0, -2, 0), utility::Vector(0.8018, 0.2673, 0.5345)},
      {utility::Point(0, 0, -2), utility::Vector(0.5345, 0.8018, 0.2673)},
      {utility::Point(2, 0, 2), utility::Vector(0, 0, -1)},
      {utility::Point(0, 2, 2), utility::Vector(0, -1, 0)},
      {utility::Point(2, 2, 0), utility::Vector(-1, 0, 0)}};

  for (auto &example : examples) {
    auto cube = std::make_unique<geometry::Cube>();
    auto ray = utility::Ray(example.origin, example.direction);
    auto xs = cube->LocalIntersect(ray);
    EXPECT_EQ(0, xs.size());
  }
}

TEST(CubeTest, TheNormalOnTheSurfaceOfACube) {
  struct Example {
    utility::Point point;
    utility::Vector normal;
  };
  std::vector<Example> examples{
      {utility::Point(1, 0.5, -0.8), utility::Vector(1, 0, 0)},
      {utility::Point(-1, -0.2, 0.9), utility::Vector(-1, 0, 0)},
      {utility::Point(-0.4, 1, -0.1), utility::Vector(0, 1, 0)},
      {utility::Point(0.3, -1, 0.7), utility::Vector(0, -1, 0)},
      {utility::Point(-0.6, 0.3, 1), utility::Vector(0, 0, 1)},
      {utility::Point(0.4, 0.4, -1), utility::Vector(0, 0, -1)},
      {utility::Point(1, 1, 1), utility::Vector(1, 0, 0)},
      {utility::Point(-1, -1, -1), utility::Vector(-1, 0, 0)}};

  for (auto &example : examples) {
    auto cube = std::make_unique<geometry::Cube>();
    auto normal = cube->LocalNormalAt(example.point);
    EXPECT_TRUE(example.normal == normal);
  }
}