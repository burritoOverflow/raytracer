#include "Material.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(MaterialTests, DefaultMaterial) {
  material::Material m;
  EXPECT_TRUE(utility::Color(1, 1, 1) == m.color_);
  ASSERT_DOUBLE_EQ(0.1, m.ambient_);
  ASSERT_DOUBLE_EQ(0.9, m.diffuse_);
  ASSERT_DOUBLE_EQ(0.9, m.specular_);
  ASSERT_DOUBLE_EQ(200.0, m.shininess_);
}