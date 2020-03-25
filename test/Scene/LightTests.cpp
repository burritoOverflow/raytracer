#include "Light.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(LightTests, PointLightHasPositionAndIntensity) {
  utility::Point position(0, 0, 0);
  utility::Color intensity(1, 1, 1);
  scene::PointLight light(position, intensity);
  EXPECT_TRUE(position == light.position_);
  EXPECT_TRUE(intensity == light.intensity_);
}