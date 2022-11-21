#include "GradientPattern.h"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

const Color black(0, 0, 0);
const Color white(1, 1, 1);

TEST(GradientPatternTest, AGradientLinearlyInterpolatesBetweenColors) {
  pattern::GradientPattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(Point(0, 0, 0)));
  EXPECT_TRUE(Color(0.75, 0.75, 0.75) == pattern.PatternAt(Point(0.25, 0, 0)));
  EXPECT_TRUE(Color(0.5, 0.5, 0.5) == pattern.PatternAt(Point(0.5, 0, 0)));
  EXPECT_TRUE(Color(0.25, 0.25, 0.25) == pattern.PatternAt(Point(0.75, 0, 0)));
}
