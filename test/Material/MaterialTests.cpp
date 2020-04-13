#include "Material.h"

#include <gtest/gtest.h>

#include "Light.h"
#include "Vector.h"

using namespace raytracer;

TEST(MaterialTest, DefaultMaterial) {
  material::Material m;
  EXPECT_TRUE(utility::Color(1, 1, 1) == m.color_);
  ASSERT_DOUBLE_EQ(0.1, m.ambient_);
  ASSERT_DOUBLE_EQ(0.9, m.diffuse_);
  ASSERT_DOUBLE_EQ(0.9, m.specular_);
  ASSERT_DOUBLE_EQ(200.0, m.shininess_);
}

TEST(MaterialTest, LightingWithAPatternApplied) {
  material::Material m;
  m.pattern_ =
      pattern::StripePattern(utility::Color(1, 1, 1), utility::Color(0, 0, 0));
  m.ambient_ = 1;
  m.diffuse_ = 0;
  m.specular_ = 0;
  utility::Vector eye_vector(0, 0, -1);
  utility::Vector normal_vector(0, 0, -1);
  scene::PointLight light(utility::Point(0, 0, -10), utility::Color(1, 1, 1));
  utility::Color c1 = Lighting(m, light, utility::Point(0.9, 0, 0), eye_vector,
                               normal_vector, false);
  utility::Color c2 = Lighting(m, light, utility::Point(1.1, 0, 0), eye_vector,
                               normal_vector, false);
  EXPECT_TRUE(utility::Color(1, 1, 1) == c1);
  EXPECT_TRUE(utility::Color(0, 0, 0) == c2);
}