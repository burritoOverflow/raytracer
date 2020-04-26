#include "Pattern.h"

#include <gtest/gtest.h>

#include "Sphere.h"

using namespace raytracer;

TEST(PatternTest, TheDefaultPatternTransformation) {
  pattern::TestPattern pattern;
  EXPECT_TRUE(utility::Identity() == pattern.transform_);
}

TEST(PatternTest, AssigningATransformation) {
  pattern::TestPattern pattern;
  pattern.transform_ = utility::Translation(1, 2, 3);
  EXPECT_TRUE(utility::Translation(1, 2, 3) == pattern.transform_);
}

TEST(PatternTest, APatternWithAnObjecTransformation) {
  geometry::Sphere shape;
  shape.transform_ = utility::Scaling(2, 2, 2);
  pattern::TestPattern pattern;
  utility::Color c =
      pattern.PatternAtShape(shape.transform_, utility::Point(2, 3, 4));
  EXPECT_TRUE(utility::Color(1, 1.5, 2) == c);
}

TEST(PatternTest, APatternWithAPatternTransformation) {
  geometry::Sphere shape;
  pattern::TestPattern pattern;
  pattern.transform_ = utility::Scaling(2, 2, 2);
  utility::Color c =
      pattern.PatternAtShape(shape.transform_, utility::Point(2, 3, 4));
  EXPECT_TRUE(utility::Color(1, 1.5, 2) == c);
}

TEST(PatternTest, APatternWithBothAnObjectAndAPatternTransformation) {
  geometry::Sphere shape;
  shape.transform_ = utility::Scaling(2, 2, 2);
  pattern::TestPattern pattern;
  pattern.transform_ = utility::Translation(0.5, 1, 1.5);
  utility::Color c =
      pattern.PatternAtShape(shape.transform_, utility::Point(2.5, 3, 3.5));
  EXPECT_TRUE(utility::Color(0.75, 0.5, 0.25) == c);
}
