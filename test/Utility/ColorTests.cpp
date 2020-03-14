#include "Color.h"

#include <gtest/gtest.h>

TEST(ColorTests, ColorsAreTuples) {
  raytracer::Color c(-0.5, 0.4, 0.7);
  ASSERT_DOUBLE_EQ(c.red(), -0.5);
  ASSERT_DOUBLE_EQ(c.green(), 0.4);
  ASSERT_DOUBLE_EQ(c.blue(), 0.7);
}

TEST(ColorTests, AddColors) {
  raytracer::Color c1(0.9, 0.6, 0.75);
  raytracer::Color c2(0.7, 0.1, 0.25);
  raytracer::Color c_sum(1.6, 0.7, 1.0);
  EXPECT_TRUE(c_sum == c1 + c2);
}

TEST(ColorTests, SubtractColors) {
  raytracer::Color c1(0.9, 0.6, 0.75);
  raytracer::Color c2(0.7, 0.1, 0.25);
  raytracer::Color c_sum(0.2, 0.5, 0.5);
  EXPECT_TRUE(c_sum == c1 - c2);
}

TEST(ColorTests, MultiplyColorsByScalar) {
  raytracer::Color c(0.2, 0.3, 0.4);
  raytracer::Color c_multiplied(0.4, 0.6, 0.8);
  EXPECT_TRUE(c_multiplied == c * 2);
}

TEST(ColorTests, MultiplyColors) {
  raytracer::Color c1(1, 0.2, 0.4);
  raytracer::Color c2(0.9, 1, 0.1);
  raytracer::Color c_multiplied(0.9, 0.2, 0.04);
  EXPECT_TRUE(c_multiplied == c1 * c2);
}
