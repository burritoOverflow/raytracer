#include "GradientPattern.h"

#include <gtest/gtest.h>

using namespace raytracer;

const utility::Color black(0, 0, 0);
const utility::Color white(1, 1, 1);

TEST(GradientPatternTest, AGradientLinearlyInterpolatesBetweenColors) {
  pattern::GradientPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(utility::Color(0.75, 0.75, 0.75) ==
              pattern.PatternAt(utility::Point(0.25, 0, 0)));
  EXPECT_TRUE(utility::Color(0.5, 0.5, 0.5) ==
              pattern.PatternAt(utility::Point(0.5, 0, 0)));
  EXPECT_TRUE(utility::Color(0.25, 0.25, 0.25) ==
              pattern.PatternAt(utility::Point(0.75, 0, 0)));
}
