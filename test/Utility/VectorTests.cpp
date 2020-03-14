#include "Vector.h"

#include <gtest/gtest.h>

TEST(VectorTests, VectorCreatesAVectorTuple) {
  raytracer::Tuple a(4, -4, 3, 0);
  raytracer::Vector v(4, -4, 3);
  for (int i = 0; i < 4; ++i) {
    ASSERT_DOUBLE_EQ(a[i], v[i])
        << "The vector and tuple differ at index " << i;
  }
}

TEST(VectorTests, SubtractVectorFromTheZeroVector) {
  raytracer::Vector zero(0, 0, 0);
  raytracer::Vector v(1, 2, 3);
  raytracer::Vector v_difference(-1, -2, -3);
  EXPECT_TRUE(v_difference == zero - v);
}

TEST(VectorTests, CrossProductOfTwoVectors) {
  raytracer::Vector a(1, 2, 3);
  raytracer::Vector b(2, 3, 4);
  raytracer::Vector a_cross_b(-1, 2, -1);
  raytracer::Vector b_cross_a(1, -2, 1);
  EXPECT_TRUE(a_cross_b == a.cross(b));
  EXPECT_TRUE(b_cross_a == b.cross(a));
}
