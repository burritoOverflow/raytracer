#include "CheckersPattern.h"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

const Color black(0, 0, 0);
const Color white(1, 1, 1);

TEST(CheckersPatternTest, CheckersShouldRepeatInX) {
  pattern::CheckersPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(Point(0.99, 0, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(Point(1.01, 0, 0)));
}

TEST(CheckersPatternTest, CheckersShouldRepeatInY) {
  pattern::CheckersPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(Point(0, 0.99, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(Point(0, 1.01, 0)));
}

TEST(CheckersPatternTest, CheckersShouldRepeatInZ) {
  pattern::CheckersPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(Point(0, 0, 0.99)));
  EXPECT_TRUE(black == pattern.PatternAt(Point(0, 0, 1.01)));
}