#include "Color.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(ColorTests, ColorsAreTuples) {
  utility::Color c(-0.5, 0.4, 0.7);
  ASSERT_DOUBLE_EQ(c.red(), -0.5);
  ASSERT_DOUBLE_EQ(c.green(), 0.4);
  ASSERT_DOUBLE_EQ(c.blue(), 0.7);
}

TEST(ColorTests, AddColors) {
  utility::Color c1(0.9, 0.6, 0.75);
  utility::Color c2(0.7, 0.1, 0.25);
  utility::Color c_sum(1.6, 0.7, 1.0);
  EXPECT_TRUE(c_sum == c1 + c2);
}

TEST(ColorTests, SubtractColors) {
  utility::Color c1(0.9, 0.6, 0.75);
  utility::Color c2(0.7, 0.1, 0.25);
  utility::Color c_sum(0.2, 0.5, 0.5);
  EXPECT_TRUE(c_sum == c1 - c2);
}

TEST(ColorTests, MultiplyColorsByScalar) {
  utility::Color c(0.2, 0.3, 0.4);
  utility::Color c_multiplied(0.4, 0.6, 0.8);
  EXPECT_TRUE(c_multiplied == c * 2);
}

TEST(ColorTests, MultiplyColors) {
  utility::Color c1(1, 0.2, 0.4);
  utility::Color c2(0.9, 1, 0.1);
  utility::Color c_multiplied(0.9, 0.2, 0.04);
  EXPECT_TRUE(c_multiplied == c1 * c2);
}
