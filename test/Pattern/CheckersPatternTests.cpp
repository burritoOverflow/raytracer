#include "CheckersPattern.h"

#include <gtest/gtest.h>

using namespace raytracer;

const utility::Color black(0, 0, 0);
const utility::Color white(1, 1, 1);

TEST(CheckersPatternTest, CheckersShouldRepeatInX) {
  pattern::CheckersPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0.99, 0, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(1.01, 0, 0)));
}

TEST(CheckersPatternTest, CheckersShouldRepeatInY) {
  pattern::CheckersPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0.99, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(0, 1.01, 0)));
}

TEST(CheckersPatternTest, CheckersShouldRepeatInZ) {
  pattern::CheckersPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0.99)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(0, 0, 1.01)));
}