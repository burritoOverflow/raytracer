#include "Vector.h"

#include <gtest/gtest.h>

using namespace raytracer;

TEST(VectorTests, VectorCreatesAVectorTuple) {
  utility::Tuple a(4, -4, 3, 0);
  utility::Vector v(4, -4, 3);
  for (size_t i = 0; i < 4; ++i) {
    ASSERT_DOUBLE_EQ(a[i], v[i])
        << "The vector and tuple differ at index " << i;
  }
}

TEST(VectorTests, SubtractVectorFromTheZeroVector) {
  utility::Vector zero(0, 0, 0);
  utility::Vector v(1, 2, 3);
  utility::Vector v_difference(-1, -2, -3);
  EXPECT_TRUE(v_difference == zero - v);
}

TEST(VectorTests, CrossProductOfTwoVectors) {
  utility::Vector a(1, 2, 3);
  utility::Vector b(2, 3, 4);
  utility::Vector a_cross_b(-1, 2, -1);
  utility::Vector b_cross_a(1, -2, 1);
  EXPECT_TRUE(a_cross_b == a.cross(b));
  EXPECT_TRUE(b_cross_a == b.cross(a));
}
