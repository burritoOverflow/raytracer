#include "Tuple.h"

#include <gtest/gtest.h>

#include "Point.h"
#include "Vector.h"

using namespace raytracer;

TEST(TupleTests, PointTupleIsAPoint) {
  utility::Tuple a(4.3, -4.2, 3.1, 1);
  ASSERT_DOUBLE_EQ(a.x(), 4.3);
  ASSERT_DOUBLE_EQ(a.y(), -4.2);
  ASSERT_DOUBLE_EQ(a.z(), 3.1);
  ASSERT_DOUBLE_EQ(a.w(), 1.0);
  EXPECT_TRUE(a.IsPoint());
  EXPECT_FALSE(a.IsVector());
}

TEST(TupleTests, VectorTupleIsAVector) {
  utility::Tuple a(4.3, -4.2, 3.1, 0);
  ASSERT_DOUBLE_EQ(a.x(), 4.3);
  ASSERT_DOUBLE_EQ(a.y(), -4.2);
  ASSERT_DOUBLE_EQ(a.z(), 3.1);
  ASSERT_DOUBLE_EQ(a.w(), 0.0);
  EXPECT_TRUE(a.IsVector());
  EXPECT_FALSE(a.IsPoint());
}

TEST(TupleTests, AddTuples) {
  utility::Tuple a1(3, -2, 5, 1);
  utility::Tuple a2(-2, 3, 1, 0);
  utility::Tuple a_sum(1, 1, 6, 1);
  EXPECT_TRUE(a_sum == a1 + a2);
  EXPECT_TRUE(a_sum == (a1 += a2));
}

TEST(TupleTests, SubtractPointFromPoint) {
  utility::Point p1(3, 2, 1);
  utility::Point p2(5, 6, 7);
  utility::Vector v(-2, -4, -6);
  EXPECT_TRUE(v == p1 - p2);
  EXPECT_TRUE(v == (p1 -= p2));
}

TEST(TupleTests, SubtractVectorFromPoint) {
  utility::Point p1(3, 2, 1);
  utility::Vector v(5, 6, 7);
  utility::Point p2(-2, -4, -6);
  EXPECT_TRUE(p2 == p1 - v);
  EXPECT_TRUE(p2 == (p1 -= v));
}

TEST(TupleTests, SubtractVectorFromVector) {
  utility::Point v1(3, 2, 1);
  utility::Vector v2(5, 6, 7);
  utility::Point v_difference(-2, -4, -6);
  EXPECT_TRUE(v_difference == v1 - v2);
  EXPECT_TRUE(v_difference == (v1 -= v2));
}

TEST(TupleTests, NegateTuple) {
  utility::Tuple a(1, -2, 3, -4);
  utility::Tuple a_negated(-1, 2, -3, 4);
  EXPECT_TRUE(a_negated == -a);
}

TEST(TupleTests, MultiplyTupleByScalar) {
  utility::Tuple a(1, -2, 3, -4);
  utility::Tuple a_multiplied(3.5, -7, 10.5, -14);
  EXPECT_TRUE(a_multiplied == a * 3.5);
}

TEST(TupleTests, MultiplyTupleByFraction) {
  utility::Tuple a(1, -2, 3, -4);
  utility::Tuple a_multiplied(0.5, -1, 1.5, -2);
  EXPECT_TRUE(a_multiplied == 0.5 * a);
}

TEST(TupleTests, DivideTupleByScalar) {
  utility::Tuple a(1, -2, 3, -4);
  utility::Tuple a_divided(0.5, -1, 1.5, -2);
  EXPECT_TRUE(a_divided == a / 2);
}

TEST(TupleTests, ComputeMagnitudeOfVector) {
  utility::Vector v1(1, 0, 0);
  ASSERT_DOUBLE_EQ(1, v1.Magnitude());

  utility::Vector v2(1, 0, 0);
  ASSERT_DOUBLE_EQ(1, v2.Magnitude());

  utility::Vector v3(1, 0, 0);
  ASSERT_DOUBLE_EQ(1, v3.Magnitude());

  utility::Vector v4(1, 2, 3);
  ASSERT_DOUBLE_EQ(sqrt(14), v4.Magnitude());

  utility::Vector v5(-1, -2, -3);
  ASSERT_DOUBLE_EQ(sqrt(14), v5.Magnitude());
}

TEST(TupleTests, NormalizeVector) {
  utility::Vector v1(4, 0, 0);
  utility::Vector v1_normalized(1, 0, 0);
  EXPECT_TRUE(v1_normalized == v1.Normalize());

  utility::Vector v2(1, 2, 3);
  utility::Vector v2_normalized(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14));
  EXPECT_TRUE(v2_normalized == v2.Normalize());

  utility::Vector v3(1, 2, 3);
  ASSERT_DOUBLE_EQ(1, v3.Normalize().Magnitude());
}

TEST(TupleTests, DotProductOfTwoVectors) {
  utility::Vector a(1, 2, 3);
  utility::Vector b(2, 3, 4);
  ASSERT_DOUBLE_EQ(20, a.Dot(b));
}
