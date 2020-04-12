#include "Shape.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(ShapeTest, TheDefaultTransformation) {
  geometry::TestShape s;
  EXPECT_TRUE(utility::Identity() == s.transform_);
}

TEST(ShapeTest, AssigningATransformation) {
  geometry::TestShape s;
  s.SetTransform(utility::Translation(2, 3, 4));
  EXPECT_TRUE(utility::Translation(2, 3, 4) == s.transform_);
}

TEST(ShapeTest, TheDefaultMaterial) {
  geometry::TestShape s;
  EXPECT_TRUE(material::Material() == s.material_);
}

TEST(ShapeTest, AddigningAMaterial) {
  geometry::TestShape s;
  material::Material m;
  m.ambient_ = 1;
  s.material_ = m;
  EXPECT_TRUE(m == s.material_);
}
