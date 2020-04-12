#include "Shape.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(ShapeTest, TheDefaultTransformation) {
  auto s = std::make_shared<geometry::TestShape>();
  EXPECT_TRUE(utility::Identity() == s->transform_);
}

TEST(ShapeTest, AssigningATransformation) {
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(utility::Translation(2, 3, 4));
  EXPECT_TRUE(utility::Translation(2, 3, 4) == s->transform_);
}

TEST(ShapeTest, TheDefaultMaterial) {
  auto s = std::make_shared<geometry::TestShape>();
  EXPECT_TRUE(material::Material() == s->material_);
}

TEST(ShapeTest, AddigningAMaterial) {
  auto s = std::make_shared<geometry::TestShape>();
  material::Material m;
  m.ambient_ = 1;
  s->material_ = m;
  EXPECT_TRUE(m == s->material_);
}

TEST(ShapeTest, IntersectingAScaledShapeWithARay) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(utility::Scaling(2, 2, 2));
  auto xs = s->Intersect(r);
  EXPECT_TRUE(utility::Point(0, 0, -2.5) == s->saved_ray_.origin_);
  EXPECT_TRUE(utility::Vector(0, 0, 0.5) == s->saved_ray_.direction_);
}

TEST(ShapeTest, IntersectingATranslatedShapeWithARay) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(utility::Translation(5, 0, 0));
  auto xs = s->Intersect(r);
  EXPECT_TRUE(utility::Point(-5, 0, -5) == s->saved_ray_.origin_);
  EXPECT_TRUE(utility::Vector(0, 0, 1) == s->saved_ray_.direction_);
}

TEST(ShapeTest, ComputingTheNormalOnATranslatedShape) {
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(utility::Translation(0, 1, 0));
  utility::Vector n = s->NormalAt(utility::Point(0, 1.70711, -0.70711));
  std::cout << std::setprecision(17);
  std::cout << n << std::endl;
  EXPECT_TRUE(utility::Vector(0, 0.70710678118654746, -0.70710678118654757) ==
              n);
}

TEST(ShapeTest, ComputingTheNormalOnATransformedShape) {
  auto s = std::make_shared<geometry::TestShape>();
  utility::Matrix m =
      utility::Scaling(1, 0.5, 1) * utility::RotationZ(M_PI / 5);
  s->SetTransform(m);
  utility::Vector n = s->NormalAt(utility::Point(0, sqrt(2) / 2, -sqrt(2) / 2));
  std::cout << std::setprecision(17);
  std::cout << n << std::endl;
  EXPECT_TRUE(utility::Vector(0, 0.97014250014533188, -0.24253562503633294) ==
              n);
}
