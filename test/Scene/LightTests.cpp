#include "Light.h"

#include <gtest/gtest.h>

#include "Material.h"

using namespace raytracer;

struct LightTests : public ::testing::Test {
  material::Material m;
  utility::Point position;

  virtual void SetUp() override {
    m = material::Material();
    position = utility::Point(0, 0, 0);
  }
};

TEST_F(LightTests, PointLightHasPositionAndIntensity) {
  utility::Point position(0, 0, 0);
  utility::Color intensity(1, 1, 1);
  scene::PointLight light(position, intensity);
  EXPECT_TRUE(position == light.position_);
  EXPECT_TRUE(intensity == light.intensity_);
}

TEST_F(LightTests, LightingWithEyeBetweenLightAndSurface) {
  utility::Vector eye_vector(0, 0, -1);
  utility::Vector normal_vector(0, 0, -1);
  scene::PointLight light(utility::Point(0, 0, -10), utility::Color(1, 1, 1));
  utility::Color result =
      scene::Lighting(m, utility::Identity(), light, position, eye_vector,
                      normal_vector, false);
  EXPECT_TRUE(utility::Color(1.9, 1.9, 1.9) == result);
}

TEST_F(LightTests,
       LightingWithEyeBetweenLightAndSurfaceWithEyeOffset45Degrees) {
  utility::Vector eye_vector(0, sqrt(2) / 2, -sqrt(2) / 2);
  utility::Vector normal_vector(0, 0, -1);
  scene::PointLight light(utility::Point(0, 0, -10), utility::Color(1, 1, 1));
  utility::Color result =
      scene::Lighting(m, utility::Identity(), light, position, eye_vector,
                      normal_vector, false);
  EXPECT_TRUE(utility::Color(1.0, 1.0, 1.0) == result);
}

TEST_F(LightTests, LightingWithEyeOppositeSurfaceWithLightOffset45Degrees) {
  utility::Vector eye_vector(0, 0, -1);
  utility::Vector normal_vector(0, 0, -1);
  scene::PointLight light(utility::Point(0, 10, -10), utility::Color(1, 1, 1));
  utility::Color result =
      scene::Lighting(m, utility::Identity(), light, position, eye_vector,
                      normal_vector, false);
  EXPECT_TRUE(utility::Color(0.1 + 0.9 * sqrt(2) / 2, 0.1 + 0.9 * sqrt(2) / 2,
                             0.1 + 0.9 * sqrt(2) / 2) == result);
}

TEST_F(LightTests, LightingWithEyeInPathOfReflectionVector) {
  utility::Vector eye_vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
  utility::Vector normal_vector(0, 0, -1);
  scene::PointLight light(utility::Point(0, 10, -10), utility::Color(1, 1, 1));
  utility::Color result =
      scene::Lighting(m, utility::Identity(), light, position, eye_vector,
                      normal_vector, false);
  EXPECT_TRUE(utility::Color(0.1 + 0.9 * sqrt(2) / 2 + 0.9,
                             0.1 + 0.9 * sqrt(2) / 2 + 0.9,
                             0.1 + 0.9 * sqrt(2) / 2 + 0.9) == result);
}

TEST_F(LightTests, LightingWithLightBehindSurface) {
  utility::Vector eye_vector(0, 0, -1);
  utility::Vector normal_vector(0, 0, -1);
  scene::PointLight light(utility::Point(0, 0, 10), utility::Color(1, 1, 1));
  utility::Color result =
      scene::Lighting(m, utility::Identity(), light, position, eye_vector,
                      normal_vector, false);
  EXPECT_TRUE(utility::Color(0.1, 0.1, 0.1) == result);
}

TEST_F(LightTests, LightingWithSurfaceInShadow) {
  utility::Vector eye_vector(0, 0, -1);
  utility::Vector normal_vector(0, 0, -1);
  scene::PointLight light(utility::Point(0, 0, -10), utility::Color(1, 1, 1));
  bool in_shadow = true;
  utility::Color result =
      scene::Lighting(m, utility::Identity(), light, position, eye_vector,
                      normal_vector, in_shadow);
  EXPECT_TRUE(utility::Color(0.1, 0.1, 0.1) == result);
}
