#include "Pattern.hpp"

#include <gtest/gtest.h>

#include "Sphere.hpp"

using namespace raytracer;
using namespace utility;

TEST(PatternTest, TheDefaultPatternTransformation) {
  pattern::TestPattern pattern;
  EXPECT_TRUE(Identity() == pattern.transform_);
}

TEST(PatternTest, AssigningATransformation) {
  pattern::TestPattern pattern;
  pattern.transform_ = Translation(1, 2, 3);
  EXPECT_TRUE(Translation(1, 2, 3) == pattern.transform_);
}

TEST(PatternTest, APatternWithAnObjecTransformation) {
  geometry::Sphere shape;
  shape.transform_ = Scaling(2, 2, 2);
  pattern::TestPattern pattern;
  Color c = pattern.PatternAtShape(shape.transform_, Point(2, 3, 4));
  EXPECT_TRUE(Color(1, 1.5, 2) == c);
}

TEST(PatternTest, APatternWithAPatternTransformation) {
  geometry::Sphere shape;
  pattern::TestPattern pattern;
  pattern.transform_ = Scaling(2, 2, 2);
  Color c = pattern.PatternAtShape(shape.transform_, Point(2, 3, 4));
  EXPECT_TRUE(Color(1, 1.5, 2) == c);
}

TEST(PatternTest, APatternWithBothAnObjectAndAPatternTransformation) {
  geometry::Sphere shape;
  shape.transform_ = Scaling(2, 2, 2);
  pattern::TestPattern pattern;
  pattern.transform_ = Translation(0.5, 1, 1.5);
  Color c = pattern.PatternAtShape(shape.transform_, Point(2.5, 3, 3.5));
  EXPECT_TRUE(Color(0.75, 0.5, 0.25) == c);
}
