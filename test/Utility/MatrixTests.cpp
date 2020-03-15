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

TEST(MatrixTests, CalculateDeterminantOf2x2Matrix) {
  raytracer::Matrix a({{1, 5}, {-3, 2}});
  ASSERT_DOUBLE_EQ(17, a.Determinant());
}

TEST(MatrixTests, SubmatrixOf3x3MatrixIs2x2Matrix) {
  raytracer::Matrix a({
      {1, 5, 0},
      {-3, 2, 7},
      {0, 6, -3},
  });
  raytracer::Matrix a_submatrix({{-3, 2}, {0, 6}});
  EXPECT_TRUE(a_submatrix == a.Submatrix(0, 2));
}

TEST(MatrixTests, SubmatrixOf4x4MatrixIs3x3Matrix) {
  raytracer::Matrix a(
      {{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}});
  raytracer::Matrix a_submatrix({
      {-6, 1, 6},
      {-8, 8, 6},
      {-7, -1, 1},
  });
  EXPECT_TRUE(a_submatrix == a.Submatrix(2, 1));
}

TEST(MatrixTests, CalculateMinorOf3x3Matrix) {
  raytracer::Matrix a({
      {3, 5, 0},
      {2, -1, -7},
      {6, -1, 5},
  });
  raytracer::Matrix b = a.Submatrix(1, 0);
  ASSERT_DOUBLE_EQ(25, b.Determinant());
  ASSERT_DOUBLE_EQ(25, a.Minor(1, 0));
}

TEST(MatrixTests, CalculateCofactorOf3x3Matrix) {
  raytracer::Matrix a({
      {3, 5, 0},
      {2, -1, -7},
      {6, -1, 5},
  });
  ASSERT_DOUBLE_EQ(-12, a.Minor(0, 0));
  ASSERT_DOUBLE_EQ(-12, a.Cofactor(0, 0));
  ASSERT_DOUBLE_EQ(25, a.Minor(1, 0));
  ASSERT_DOUBLE_EQ(-25, a.Cofactor(1, 0));
}

TEST(MatrixTests, CalculateDeterminantOf3x3Matrix) {
  raytracer::Matrix a({
      {1, 2, 6},
      {-5, 8, -4},
      {2, 6, 4},
  });
  ASSERT_DOUBLE_EQ(56, a.Cofactor(0, 0));
  ASSERT_DOUBLE_EQ(12, a.Cofactor(0, 1));
  ASSERT_DOUBLE_EQ(-46, a.Cofactor(0, 2));
  ASSERT_DOUBLE_EQ(-196, a.Determinant());
}

TEST(MatrixTests, CalculateDeterminantOf4x4Matrix) {
  raytracer::Matrix a(
      {{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}});
  ASSERT_DOUBLE_EQ(690, a.Cofactor(0, 0));
  ASSERT_DOUBLE_EQ(447, a.Cofactor(0, 1));
  ASSERT_DOUBLE_EQ(210, a.Cofactor(0, 2));
  ASSERT_DOUBLE_EQ(51, a.Cofactor(0, 3));
  ASSERT_DOUBLE_EQ(-4071, a.Determinant());
}

TEST(MatrixTests, TestInvertibleMatrixForInvertibility) {
  raytracer::Matrix a(
      {{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}});
  ASSERT_DOUBLE_EQ(-2120, a.Determinant());
  EXPECT_TRUE(a.IsInvertible());
}

TEST(MatrixTests, TestNoninvertibleMatrixForInvertibility) {
  raytracer::Matrix a(
      {{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}});
  ASSERT_DOUBLE_EQ(0, a.Determinant());
  EXPECT_FALSE(a.IsInvertible());
}

TEST(MatrixTests, CalculateInverseOfMatrix) {
  raytracer::Matrix a(
      {{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}});
  raytracer::Matrix a_inverse(
      {{116. / 532, 240. / 532, 128. / 532, -24. / 532},
       {-430. / 532, -775. / 532, -236. / 532, 277. / 532},
       {-42. / 532, -119. / 532, -28. / 532, 105. / 532},
       {-278. / 532, -433. / 532, -160. / 532, 163. / 532}});
  raytracer::Matrix b = a.Inverse();
  ASSERT_DOUBLE_EQ(532, a.Determinant());
  ASSERT_DOUBLE_EQ(-160, a.Cofactor(2, 3));
  ASSERT_DOUBLE_EQ(-160. / 532, b.GetElement(3, 2));
  ASSERT_DOUBLE_EQ(105, a.Cofactor(3, 2));
  ASSERT_DOUBLE_EQ(105. / 532, b.GetElement(2, 3));
  EXPECT_TRUE(a_inverse == b);
}

TEST(MatrixTests, CalculateInverseOfAnotherMatrix) {
  raytracer::Matrix a(
      {{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}});
  raytracer::Matrix a_inverse(
      {{90. / -585, 90. / -585, 165. / -585, 315. / -585},
       {45. / -585, -72. / -585, -15. / -585, -18. / -585},
       {-210. / -585, -210. / -585, -255. / -585, -540. / -585},
       {405. / -585, 405. / -585, 450. / -585, 1125. / -585}});
  raytracer::Matrix b = a.Inverse();
  EXPECT_TRUE(a_inverse == b);
}

TEST(MatrixTests, CalculateInverseOfYetAnotherMatrix) {
  raytracer::Matrix a(
      {{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}});
  raytracer::Matrix a_inverse(
      {{-66. / 1620, -126. / 1620, 234. / 1620, -360. / 1620},
       {-126. / 1620, 54. / 1620, 594. / 1620, -540. / 1620},
       {-47. / 1620, -237. / 1620, -177. / 1620, 210. / 1620},
       {288. / 1620, 108. / 1620, -432. / 1620, 540. / 1620}});
  raytracer::Matrix b = a.Inverse();
  EXPECT_TRUE(a_inverse == b);
}

TEST(MatrixTests, MultiplyMatrixByItsInverse) {
  raytracer::Matrix a(
      {{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}});
  raytracer::Matrix b(
      {{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}});
  raytracer::Matrix c = a * b;
  EXPECT_TRUE(a == c * b.Inverse());
}
