#include "RingPattern.h"

#include <gtest/gtest.h>

using namespace raytracer;

const utility::Color black(0, 0, 0);
const utility::Color white(1, 1, 1);

TEST(RingPatternTest, ARingShouldExtendInBothXAndZ) {
  pattern::RingPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(1, 0, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(0, 0, 1)));
  // 0.708 is just slightly more than sqrt(2)/2
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(0.708, 0, 0.708)));
}
