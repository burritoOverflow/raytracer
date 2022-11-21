#include "Color.h"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(ColorTests, ColorsAreTuples) {
  Color c(-0.5, 0.4, 0.7);
  ASSERT_DOUBLE_EQ(c.red(), -0.5);
  ASSERT_DOUBLE_EQ(c.green(), 0.4);
  ASSERT_DOUBLE_EQ(c.blue(), 0.7);
}

TEST(ColorTests, AddColors) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  Color c_sum(1.6, 0.7, 1.0);
  EXPECT_TRUE(c_sum == c1 + c2);
}

TEST(ColorTests, SubtractColors) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  Color c_sum(0.2, 0.5, 0.5);
  EXPECT_TRUE(c_sum == c1 - c2);
}

TEST(ColorTests, MultiplyColorsByScalar) {
  Color c(0.2, 0.3, 0.4);
  Color c_multiplied(0.4, 0.6, 0.8);
  EXPECT_TRUE(c_multiplied == c * 2);
}

TEST(ColorTests, MultiplyColors) {
  Color c1(1, 0.2, 0.4);
  Color c2(0.9, 1, 0.1);
  Color c_multiplied(0.9, 0.2, 0.04);
  EXPECT_TRUE(c_multiplied == c1 * c2);
}
