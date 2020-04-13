#include "StripePattern.h"

#include <gtest/gtest.h>

using namespace raytracer;

const utility::Color black(0, 0, 0);
const utility::Color white(1, 1, 1);

TEST(StripePatternTest, CreatingAStripedPattern) {
  pattern::StripePattern pattern(white, black);
  EXPECT_TRUE(white == pattern.a_);
  EXPECT_TRUE(black == pattern.b_);
}

TEST(StripePatternTest, AStripePatternIsConstantInY) {
  pattern::StripePattern pattern(white, black);
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0, 1, 0)));
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0, 2, 0)));
}

TEST(StripePatternTest, AStripePatternIsConstantInZ) {
  pattern::StripePattern pattern(white, black);
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0, 0, 1)));
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0, 0, 2)));
}

TEST(StripePatternTest, AStripePatternAlternatesInX) {
  pattern::StripePattern pattern(white, black);
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(0.9, 0, 0)));
  EXPECT_TRUE(black == pattern.StripeAt(utility::Point(1, 0, 0)));
  EXPECT_TRUE(black == pattern.StripeAt(utility::Point(-0.1, 0, 0)));
  EXPECT_TRUE(black == pattern.StripeAt(utility::Point(-1, 0, 0)));
  EXPECT_TRUE(white == pattern.StripeAt(utility::Point(-1.1, 0, 0)));
}
