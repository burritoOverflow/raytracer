#include "Tuple.h"

#include <gtest/gtest.h>

#include "Point.h"
#include "Vector.h"

TEST(TupleTests, PointTupleIsAPoint) {
  raytracer::Tuple a(4.3, -4.2, 3.1, 1);
  ASSERT_DOUBLE_EQ(a.x(), 4.3);
  ASSERT_DOUBLE_EQ(a.y(), -4.2);
  ASSERT_DOUBLE_EQ(a.z(), 3.1);
  ASSERT_DOUBLE_EQ(a.w(), 1.0);
  EXPECT_TRUE(a.IsPoint());
  EXPECT_FALSE(a.IsVector());
}

TEST(TupleTests, VectorTupleIsAVector) {
  raytracer::Tuple a(4.3, -4.2, 3.1, 0);
  ASSERT_DOUBLE_EQ(a.x(), 4.3);
  ASSERT_DOUBLE_EQ(a.y(), -4.2);
  ASSERT_DOUBLE_EQ(a.z(), 3.1);
  ASSERT_DOUBLE_EQ(a.w(), 0.0);
  EXPECT_TRUE(a.IsVector());
  EXPECT_FALSE(a.IsPoint());
}

TEST(TupleTests, AddTuples) {
  raytracer::Tuple a1(3, -2, 5, 1);
  raytracer::Tuple a2(-2, 3, 1, 0);
  raytracer::Tuple a_sum(1, 1, 6, 1);
  EXPECT_TRUE(a_sum == a1 + a2);
  EXPECT_TRUE(a_sum == (a1 += a2));
}

TEST(TupleTests, SubtractPointFromPoint) {
  raytracer::Point p1(3, 2, 1);
  raytracer::Point p2(5, 6, 7);
  raytracer::Vector v(-2, -4, -6);
  EXPECT_TRUE(v == p1 - p2);
  EXPECT_TRUE(v == (p1 -= p2));
}

TEST(TupleTests, SubtractVectorFromPoint) {
  raytracer::Point p1(3, 2, 1);
  raytracer::Vector v(5, 6, 7);
  raytracer::Point p2(-2, -4, -6);
  EXPECT_TRUE(p2 == p1 - v);
  EXPECT_TRUE(p2 == (p1 -= v));
}

TEST(TupleTests, SubtractVectorFromVector) {
  raytracer::Point v1(3, 2, 1);
  raytracer::Vector v2(5, 6, 7);
  raytracer::Point v_difference(-2, -4, -6);
  EXPECT_TRUE(v_difference == v1 - v2);
  EXPECT_TRUE(v_difference == (v1 -= v2));
}

TEST(TupleTests, NegateTuple) {
  raytracer::Tuple a(1, -2, 3, -4);
  raytracer::Tuple a_negated(-1, 2, -3, 4);
  EXPECT_TRUE(a_negated == -a);
}

TEST(TupleTests, MultiplyTupleByScalar) {
  raytracer::Tuple a(1, -2, 3, -4);
  raytracer::Tuple a_multiplied(3.5, -7, 10.5, -14);
  EXPECT_TRUE(a_multiplied == a * 3.5);
}

TEST(TupleTests, MultiplyTupleByFraction) {
  raytracer::Tuple a(1, -2, 3, -4);
  raytracer::Tuple a_multiplied(0.5, -1, 1.5, -2);
  EXPECT_TRUE(a_multiplied == 0.5 * a);
}

TEST(TupleTests, DivideTupleByScalar) {
  raytracer::Tuple a(1, -2, 3, -4);
  raytracer::Tuple a_divided(0.5, -1, 1.5, -2);
  EXPECT_TRUE(a_divided == a / 2);
}

TEST(TupleTests, ComputeMagnitudeOfVector) {
  raytracer::Vector v1(1, 0, 0);
  ASSERT_DOUBLE_EQ(1, v1.Magnitude());

  raytracer::Vector v2(1, 0, 0);
  ASSERT_DOUBLE_EQ(1, v2.Magnitude());

  raytracer::Vector v3(1, 0, 0);
  ASSERT_DOUBLE_EQ(1, v3.Magnitude());

  raytracer::Vector v4(1, 2, 3);
  ASSERT_DOUBLE_EQ(sqrt(14), v4.Magnitude());

  raytracer::Vector v5(-1, -2, -3);
  ASSERT_DOUBLE_EQ(sqrt(14), v5.Magnitude());
}

TEST(TupleTests, NormalizeVector) {
  raytracer::Vector v1(4, 0, 0);
  raytracer::Vector v1_normalized(1, 0, 0);
  EXPECT_TRUE(v1_normalized == v1.Normalize());

  raytracer::Vector v2(1, 2, 3);
  raytracer::Vector v2_normalized(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14));
  EXPECT_TRUE(v2_normalized == v2.Normalize());

  raytracer::Vector v3(1, 2, 3);
  ASSERT_DOUBLE_EQ(1, v3.Normalize().Magnitude());
}

TEST(TupleTests, DotProductOfTwoVectors) {
  raytracer::Vector a(1, 2, 3);
  raytracer::Vector b(2, 3, 4);
  ASSERT_DOUBLE_EQ(20, a.Dot(b));
}
