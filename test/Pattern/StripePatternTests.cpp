#include "StripePattern.h"

#include <gtest/gtest.h>

#include "Sphere.h"

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
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 1, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 2, 0)));
}

TEST(StripePatternTest, AStripePatternIsConstantInZ) {
  pattern::StripePattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 1)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 2)));
}

TEST(StripePatternTest, AStripePatternAlternatesInX) {
  pattern::StripePattern pattern(white, black);
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(0.9, 0, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(1, 0, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(-0.1, 0, 0)));
  EXPECT_TRUE(black == pattern.PatternAt(utility::Point(-1, 0, 0)));
  EXPECT_TRUE(white == pattern.PatternAt(utility::Point(-1.1, 0, 0)));
}

TEST(StripePatternTest, StripesWithAnObjectTransformation) {
  auto object = std::make_shared<geometry::Sphere>();
  object->SetTransform(utility::Scaling(2, 2, 2));
  pattern::StripePattern pattern(white, black);
  utility::Color c =
      pattern.PatternAtShape(object->transform_, utility::Point(1.5, 0, 0));
  EXPECT_TRUE(white == c);
}

TEST(StripePatternTest, StripesWithAPatternTransformation) {
  auto object = std::make_shared<geometry::Sphere>();
  pattern::StripePattern pattern(white, black);
  pattern.transform_ = utility::Scaling(2, 2, 2);
  utility::Color c =
      pattern.PatternAtShape(object->transform_, utility::Point(1.5, 0, 0));
  EXPECT_TRUE(white == c);
}

TEST(StripePatternTest, StripesWithBothAnObjectAndAPatternTransformation) {
  auto object = std::make_shared<geometry::Sphere>();
  object->SetTransform(utility::Scaling(2, 2, 2));
  pattern::StripePattern pattern(white, black);
  pattern.transform_ = utility::Translation(0.5, 0, 0);
  utility::Color c =
      pattern.PatternAtShape(object->transform_, utility::Point(2.5, 0, 0));
  EXPECT_TRUE(white == c);
}
