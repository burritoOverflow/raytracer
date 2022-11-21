#include "Vector.h"

#include <gtest/gtest.h>

using namespace raytracer;
using namespace utility;

TEST(VectorTests, VectorCreatesAVectorTuple) {
  Tuple a(4, -4, 3, 0);
  Vector v(4, -4, 3);
  for (size_t i = 0; i < 4; ++i) {
    ASSERT_DOUBLE_EQ(a[i], v[i])
        << "The vector and tuple differ at index " << i;
  }
}

TEST(VectorTests, SubtractVectorFromTheZeroVector) {
  Vector zero(0, 0, 0);
  Vector v(1, 2, 3);
  Vector v_difference(-1, -2, -3);
  EXPECT_TRUE(v_difference == zero - v);
}

TEST(VectorTests, CrossProductOfTwoVectors) {
  Vector a(1, 2, 3);
  Vector b(2, 3, 4);
  Vector a_cross_b(-1, 2, -1);
  Vector b_cross_a(1, -2, 1);
  EXPECT_TRUE(a_cross_b == a.Cross(b));
  EXPECT_TRUE(b_cross_a == b.Cross(a));
}

TEST(VectorTests, ReflectVectorApproachingAt45Degrees) {
  Vector v(1, -1, 0);
  Vector n(0, 1, 0);
  Vector r = v.Reflect(n);
  EXPECT_TRUE(Vector(1, 1, 0) == r);
}

TEST(VectorTests, ReflectVectorOffSlantedSurface) {
  Vector v(0, -1, 0);
  Vector n(sqrt(2) / 2, sqrt(2) / 2, 0);
  Vector r = v.Reflect(n);
  EXPECT_TRUE(Vector(1, 0, 0) == r);
}