#include "Material.hpp"

#include <gtest/gtest.h>

#include "Light.hpp"
#include "StripePattern.hpp"
#include "Vector.hpp"

using namespace raytracer;
using namespace utility;

TEST(MaterialTest, DefaultMaterial) {
  material::Material m;
  EXPECT_TRUE(Color(1, 1, 1) == m.color_);
  ASSERT_DOUBLE_EQ(0.1, m.ambient_);
  ASSERT_DOUBLE_EQ(0.9, m.diffuse_);
  ASSERT_DOUBLE_EQ(0.9, m.specular_);
  ASSERT_DOUBLE_EQ(200.0, m.shininess_);
}

TEST(MaterialTest, LightingWithAPatternApplied) {
  material::Material m;
  m.pattern_ = std::make_shared<pattern::StripePattern>(
      pattern::StripePattern(Color(1, 1, 1), Color(0, 0, 0)));
  m.ambient_ = 1;
  m.diffuse_ = 0;
  m.specular_ = 0;
  Vector eye_vector(0, 0, -1);
  Vector normal_vector(0, 0, -1);
  scene::PointLight light(Point(0, 0, -10), Color(1, 1, 1));
  Color c1 = Lighting(m, Identity(), light, Point(0.9, 0, 0), eye_vector,
                      normal_vector, false);
  Color c2 = Lighting(m, Identity(), light, Point(1.1, 0, 0), eye_vector,
                      normal_vector, false);
  EXPECT_TRUE(Color(1, 1, 1) == c1);
  EXPECT_TRUE(Color(0, 0, 0) == c2);
}

TEST(MaterialTest, ReflectivityForTheDefaultMaterial) {
  material::Material m;
  ASSERT_DOUBLE_EQ(0.0, m.reflective_);
}

TEST(MaterialTest, TransparencyAndRefractiveIndexForTheDefaultMaterial) {
  material::Material m;
  ASSERT_DOUBLE_EQ(0.0, m.transparency_);
  ASSERT_DOUBLE_EQ(1.0, m.refractive_index_);
}
