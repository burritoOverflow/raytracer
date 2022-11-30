#include "Light.hpp"

#include <gtest/gtest.h>

#include "Material.hpp"

using namespace raytracer;
using namespace utility;

struct LightTests : public ::testing::Test {
protected:
  void SetUp() override {
    m = std::make_shared<material::Material>();
    position = Point(0, 0, 0);
  }

  std::shared_ptr<material::Material> m;
  Point position;
};

TEST_F(LightTests, PointLightHasPositionAndIntensity) {
  Color intensity(1, 1, 1);
  scene::PointLight light(position, intensity);
  EXPECT_TRUE(position == light.position_);
  EXPECT_TRUE(intensity == light.intensity_);
}

TEST_F(LightTests, LightingWithEyeBetweenLightAndSurface) {
  Vector eye_vector(0, 0, -1);
  Vector normal_vector(0, 0, -1);
  scene::PointLight light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = scene::Lighting(m, Identity(), light, position, eye_vector,
                                 normal_vector, false);
  EXPECT_TRUE(Color(1.9, 1.9, 1.9) == result);
}

TEST_F(LightTests,
       LightingWithEyeBetweenLightAndSurfaceWithEyeOffset45Degrees) {
  Vector eye_vector(0, sqrt(2) / 2, -sqrt(2) / 2);
  Vector normal_vector(0, 0, -1);
  scene::PointLight light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = scene::Lighting(m, Identity(), light, position, eye_vector,
                                 normal_vector, false);
  EXPECT_TRUE(Color(1.0, 1.0, 1.0) == result);
}

TEST_F(LightTests, LightingWithEyeOppositeSurfaceWithLightOffset45Degrees) {
  Vector eye_vector(0, 0, -1);
  Vector normal_vector(0, 0, -1);
  scene::PointLight light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = scene::Lighting(m, Identity(), light, position, eye_vector,
                                 normal_vector, false);
  EXPECT_TRUE(Color(0.1 + 0.9 * sqrt(2) / 2, 0.1 + 0.9 * sqrt(2) / 2,
                    0.1 + 0.9 * sqrt(2) / 2) == result);
}

TEST_F(LightTests, LightingWithEyeInPathOfReflectionVector) {
  Vector eye_vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
  Vector normal_vector(0, 0, -1);
  scene::PointLight light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = scene::Lighting(m, Identity(), light, position, eye_vector,
                                 normal_vector, false);
  EXPECT_TRUE(Color(0.1 + 0.9 * sqrt(2) / 2 + 0.9,
                    0.1 + 0.9 * sqrt(2) / 2 + 0.9,
                    0.1 + 0.9 * sqrt(2) / 2 + 0.9) == result);
}

TEST_F(LightTests, LightingWithLightBehindSurface) {
  Vector eye_vector(0, 0, -1);
  Vector normal_vector(0, 0, -1);
  scene::PointLight light(Point(0, 0, 10), Color(1, 1, 1));
  Color result = scene::Lighting(m, Identity(), light, position, eye_vector,
                                 normal_vector, false);
  EXPECT_TRUE(Color(0.1, 0.1, 0.1) == result);
}

TEST_F(LightTests, LightingWithSurfaceInShadow) {
  Vector eye_vector(0, 0, -1);
  Vector normal_vector(0, 0, -1);
  scene::PointLight light(Point(0, 0, -10), Color(1, 1, 1));
  bool in_shadow = true;
  Color result = scene::Lighting(m, Identity(), light, position, eye_vector,
                                 normal_vector, in_shadow);
  EXPECT_TRUE(Color(0.1, 0.1, 0.1) == result);
}
