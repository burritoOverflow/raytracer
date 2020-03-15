#include "Matrix.h"
#include "Tuple.h"

#include <gtest/gtest.h>

TEST(MatrixTests, ConstructAndInspect2x2Matrix) {
  raytracer::Matrix m({
      {-3, 5},
      {1, -2},
  });
  ASSERT_DOUBLE_EQ(-3, m(0, 0));
  ASSERT_DOUBLE_EQ(5, m(0, 1));
  ASSERT_DOUBLE_EQ(1, m(1, 0));
  ASSERT_DOUBLE_EQ(-2, m(1, 1));
}

TEST(MatrixTests, ConstructAndInspect3x3Matrix) {
  raytracer::Matrix m({
      {-3, 5, 0},
      {1, -2, -7},
      {0, 1, 1},
  });
  ASSERT_DOUBLE_EQ(-3, m(0, 0));
  ASSERT_DOUBLE_EQ(-2, m(1, 1));
  ASSERT_DOUBLE_EQ(1, m(2, 2));
}

TEST(MatrixTests, ConstructAndInspect4x4Matrix) {
  raytracer::Matrix m({{1, 2, 3, 4},
                       {5.5, 6.5, 7.5, 8.5},
                       {9, 10, 11, 12},
                       {13.5, 14.5, 15.5, 16.5}});
  ASSERT_DOUBLE_EQ(1, m(0, 0));
  ASSERT_DOUBLE_EQ(4, m(0, 3));
  ASSERT_DOUBLE_EQ(5.5, m(1, 0));
  ASSERT_DOUBLE_EQ(7.5, m(1, 2));
  ASSERT_DOUBLE_EQ(11, m(2, 2));
  ASSERT_DOUBLE_EQ(13.5, m(3, 0));
  ASSERT_DOUBLE_EQ(15.5, m(3, 2));
}

TEST(MatrixTests, MatrixEqualityWithIdenticalMatrices) {
  raytracer::Matrix a(
      {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
  raytracer::Matrix b(
      {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
  EXPECT_TRUE(a == b);
}

TEST(MatrixTests, MatrixEqualityWithDifferentMatrices) {
  raytracer::Matrix a(
      {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
  raytracer::Matrix b(
      {{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}, {14, 15, 16, 17}});
  EXPECT_TRUE(a != b);
}

TEST(MatrixTests, MultiplyTwoMatrices) {
  raytracer::Matrix a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  raytracer::Matrix b(
      {{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}});
  raytracer::Matrix a_times_b({{20, 22, 50, 48},
                               {44, 54, 114, 108},
                               {40, 58, 110, 102},
                               {16, 26, 46, 42}});
  EXPECT_TRUE(a_times_b == a * b);
}

TEST(MatrixTests, MultiplyMatrixWithTuple) {
  raytracer::Matrix a({{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}});
  raytracer::Tuple b(1, 2, 3, 1);
  raytracer::Tuple a_times_b(18, 24, 33, 1);
  EXPECT_TRUE(a_times_b == a * b);
}

TEST(MatrixTests, MultiplyMatrixByIdentityMatrix) {
  raytracer::Matrix a(
      {{0, 1, 2, 3}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}});
  raytracer::Matrix identity_matrix(
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
  EXPECT_TRUE(a == a * identity_matrix);
  EXPECT_TRUE(a == identity_matrix * a);
}

TEST(MatrixTests, MultiplyIdentityMatrixByTuple) {
  raytracer::Matrix identity_matrix(
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
  raytracer::Tuple a(1, 2, 3, 4);
  EXPECT_TRUE(a == identity_matrix * a);
}

TEST(MatrixTests, TransposeMatrix) {
  raytracer::Matrix a({{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}});
  raytracer::Matrix a_transpose(
      {{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}});
  EXPECT_TRUE(a_transpose == a.Transpose());
}

TEST(MatrixTests, TransposeIdentityMatrix) {
  raytracer::Matrix identity_matrix(
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
  EXPECT_TRUE(identity_matrix == identity_matrix.Transpose());
}