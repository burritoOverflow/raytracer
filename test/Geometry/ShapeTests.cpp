#include "Shape.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include <gtest/gtest.h>

#include "Group.hpp"
#include "Sphere.hpp"

using namespace raytracer;
using namespace utility;

TEST(ShapeTest, TheDefaultTransformation) {
  auto s = std::make_shared<geometry::TestShape>();
  EXPECT_TRUE(Identity() == s->transform_);
}

TEST(ShapeTest, AssigningATransformation) {
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(Translation(2, 3, 4));
  EXPECT_TRUE(Translation(2, 3, 4) == s->transform_);
}

TEST(ShapeTest, TheDefaultMaterial) {
  auto s = std::make_shared<geometry::TestShape>();
  EXPECT_TRUE(*std::make_shared<material::Material>() == *s->material_);
}

TEST(ShapeTest, AddingAMaterial) {
  auto s = std::make_shared<geometry::TestShape>();
  auto m = std::make_shared<material::Material>();
  m->ambient_ = 1;
  s->material_ = m;
  EXPECT_TRUE(m == s->material_);
}

TEST(ShapeTest, IntersectingAScaledShapeWithARay) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(Scaling(2, 2, 2));
  auto xs = s->Intersect(r);
  EXPECT_TRUE(Point(0, 0, -2.5) == s->saved_ray_.origin_);
  EXPECT_TRUE(Vector(0, 0, 0.5) == s->saved_ray_.direction_);
}

TEST(ShapeTest, IntersectingATranslatedShapeWithARay) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(Translation(5, 0, 0));
  auto xs = s->Intersect(r);
  EXPECT_TRUE(Point(-5, 0, -5) == s->saved_ray_.origin_);
  EXPECT_TRUE(Vector(0, 0, 1) == s->saved_ray_.direction_);
}

TEST(ShapeTest, ComputingTheNormalOnATranslatedShape) {
  auto s = std::make_shared<geometry::TestShape>();
  s->SetTransform(Translation(0, 1, 0));
  Vector n = s->NormalAt(Point(0, 1.70711, -0.70711));
  EXPECT_TRUE(Vector(0, 0.70710678118654746, -0.70710678118654757) == n);
}

TEST(ShapeTest, ComputingTheNormalOnATransformedShape) {
  auto s = std::make_shared<geometry::TestShape>();
  Matrix m = Scaling(1, 0.5, 1) * RotationZ(M_PI / 5);
  s->SetTransform(m);
  Vector n = s->NormalAt(Point(0, sqrt(2) / 2, -sqrt(2) / 2));
  EXPECT_TRUE(Vector(0, 0.97014250014533188, -0.24253562503633294) == n);
}

TEST(ShapeTest, AShapeHasAParentAttribute) {
  auto s = std::make_shared<geometry::TestShape>();
  EXPECT_EQ(nullptr, s->parent_);
}

TEST(ShapeTest, ConvertingAPointFromWorldToObjectSpace) {
  auto group1 = std::make_shared<geometry::Group>();
  group1->SetTransform(RotationY(M_PI_2));
  auto group2 = std::make_shared<geometry::Group>();
  group2->SetTransform(Scaling(2, 2, 2));
  group1->AddChild(group2);
  auto sphere = std::make_shared<geometry::Sphere>();
  sphere->SetTransform(Translation(5, 0, 0));
  group2->AddChild(sphere);

  auto point = sphere->WorldToObject(Point(-2, 0, -10));
  EXPECT_TRUE(Point(0, 0, -1) == point);
}

TEST(ShapeTest, ConvertingANormalFromObjectToWorldSpace) {
  auto group1 = std::make_shared<geometry::Group>();
  group1->SetTransform(RotationY(M_PI_2));
  auto group2 = std::make_shared<geometry::Group>();
  group2->SetTransform(Scaling(1, 2, 3));
  group1->AddChild(group2);
  auto sphere = std::make_shared<geometry::Sphere>();
  sphere->SetTransform(Translation(5, 0, 0));
  group2->AddChild(sphere);

  auto normal =
      sphere->NormalToWorld(Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  EXPECT_TRUE(Vector(0.28571428571428575, 0.42857142857142855,
                     -0.85714285714285710) == normal);
}

TEST(ShapeTest, FindingTheNormalOnAChildObject) {
  auto group1 = std::make_shared<geometry::Group>();
  group1->SetTransform(RotationY(M_PI_2));
  auto group2 = std::make_shared<geometry::Group>();
  group2->SetTransform(Scaling(1, 2, 3));
  group1->AddChild(group2);
  auto sphere = std::make_shared<geometry::Sphere>();
  sphere->SetTransform(Translation(5, 0, 0));
  group2->AddChild(sphere);

  auto normal = sphere->NormalAt(Point(1.7321, 1.1547, -5.5774));
  EXPECT_TRUE(Vector(0.28570368184140726, 0.42854315178114105,
                     -0.85716052944810173) == normal);
}