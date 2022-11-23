#include "Matrix.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include <gtest/gtest.h>

#include "Point.hpp"
#include "Tuple.hpp"
#include "Vector.hpp"

using namespace raytracer;
using namespace utility;

TEST(MatrixTests, ConstructAndInspect2x2Matrix) {
  Matrix m({
      {-3, 5},
      {1, -2},
  });
  ASSERT_DOUBLE_EQ(-3, m(0, 0));
  ASSERT_DOUBLE_EQ(5, m(0, 1));
  ASSERT_DOUBLE_EQ(1, m(1, 0));
  ASSERT_DOUBLE_EQ(-2, m(1, 1));
}

TEST(MatrixTests, ConstructAndInspect3x3Matrix) {
  Matrix m({
      {-3, 5, 0},
      {1, -2, -7},
      {0, 1, 1},
  });
  ASSERT_DOUBLE_EQ(-3, m(0, 0));
  ASSERT_DOUBLE_EQ(-2, m(1, 1));
  ASSERT_DOUBLE_EQ(1, m(2, 2));
}

TEST(MatrixTests, ConstructAndInspect4x4Matrix) {
  Matrix m({{1, 2, 3, 4},
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
  Matrix a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
  Matrix b({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
  EXPECT_TRUE(a == b);
}

TEST(MatrixTests, MatrixEqualityWithDifferentMatrices) {
  Matrix a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
  Matrix b({{2, 3, 4, 5}, {6, 7, 8, 9}, {10, 11, 12, 13}, {14, 15, 16, 17}});
  EXPECT_TRUE(a != b);
}

TEST(MatrixTests, MultiplyTwoMatrices) {
  Matrix a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  Matrix b({{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}});
  Matrix a_times_b({{20, 22, 50, 48},
                    {44, 54, 114, 108},
                    {40, 58, 110, 102},
                    {16, 26, 46, 42}});
  EXPECT_TRUE(a_times_b == a * b);
}

TEST(MatrixTests, MultiplyMatrixWithTuple) {
  Matrix a({{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}});
  Tuple b(1, 2, 3, 1);
  Tuple a_times_b(18, 24, 33, 1);
  EXPECT_TRUE(a_times_b == a * b);
}

TEST(MatrixTests, MultiplyMatrixByIdentityMatrix) {
  Matrix a({{0, 1, 2, 3}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}});
  Matrix identity_matrix(
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
  EXPECT_TRUE(a == a * identity_matrix);
  EXPECT_TRUE(a == identity_matrix * a);
}

TEST(MatrixTests, MultiplyIdentityMatrixByTuple) {
  Matrix identity_matrix(
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
  Tuple a(1, 2, 3, 4);
  EXPECT_TRUE(a == identity_matrix * a);
}

TEST(MatrixTests, TransposeMatrix) {
  Matrix a({{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}});
  Matrix a_transpose({{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}});
  EXPECT_TRUE(a_transpose == a.Transpose());
}

TEST(MatrixTests, TransposeIdentityMatrix) {
  Matrix identity_matrix(
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
  EXPECT_TRUE(identity_matrix == identity_matrix.Transpose());
}

TEST(MatrixTests, CalculateDeterminantOf2x2Matrix) {
  Matrix a({{1, 5}, {-3, 2}});
  ASSERT_DOUBLE_EQ(17, a.Determinant());
}

TEST(MatrixTests, SubmatrixOf3x3MatrixIs2x2Matrix) {
  Matrix a({
      {1, 5, 0},
      {-3, 2, 7},
      {0, 6, -3},
  });
  Matrix a_submatrix({{-3, 2}, {0, 6}});
  EXPECT_TRUE(a_submatrix == a.Submatrix(0, 2));
}

TEST(MatrixTests, SubmatrixOf4x4MatrixIs3x3Matrix) {
  Matrix a({{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}});
  Matrix a_submatrix({
      {-6, 1, 6},
      {-8, 8, 6},
      {-7, -1, 1},
  });
  EXPECT_TRUE(a_submatrix == a.Submatrix(2, 1));
}

TEST(MatrixTests, CalculateMinorOf3x3Matrix) {
  Matrix a({
      {3, 5, 0},
      {2, -1, -7},
      {6, -1, 5},
  });
  Matrix b = a.Submatrix(1, 0);
  ASSERT_DOUBLE_EQ(25, b.Determinant());
  ASSERT_DOUBLE_EQ(25, a.Minor(1, 0));
}

TEST(MatrixTests, CalculateCofactorOf3x3Matrix) {
  Matrix a({
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
  Matrix a({
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
  Matrix a({{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}});
  ASSERT_DOUBLE_EQ(690, a.Cofactor(0, 0));
  ASSERT_DOUBLE_EQ(447, a.Cofactor(0, 1));
  ASSERT_DOUBLE_EQ(210, a.Cofactor(0, 2));
  ASSERT_DOUBLE_EQ(51, a.Cofactor(0, 3));
  ASSERT_DOUBLE_EQ(-4071, a.Determinant());
}

TEST(MatrixTests, TestInvertibleMatrixForInvertibility) {
  Matrix a({{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}});
  ASSERT_DOUBLE_EQ(-2120, a.Determinant());
  EXPECT_TRUE(a.IsInvertible());
}

TEST(MatrixTests, TestNoninvertibleMatrixForInvertibility) {
  Matrix a({{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}});
  ASSERT_DOUBLE_EQ(0, a.Determinant());
  EXPECT_FALSE(a.IsInvertible());
}

TEST(MatrixTests, CalculateInverseOfMatrix) {
  Matrix a({{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}});
  Matrix a_inverse({{116. / 532, 240. / 532, 128. / 532, -24. / 532},
                    {-430. / 532, -775. / 532, -236. / 532, 277. / 532},
                    {-42. / 532, -119. / 532, -28. / 532, 105. / 532},
                    {-278. / 532, -433. / 532, -160. / 532, 163. / 532}});
  Matrix b = a.Inverse();
  ASSERT_DOUBLE_EQ(532, a.Determinant());
  ASSERT_DOUBLE_EQ(-160, a.Cofactor(2, 3));
  ASSERT_DOUBLE_EQ(-160. / 532, b.GetElement(3, 2));
  ASSERT_DOUBLE_EQ(105, a.Cofactor(3, 2));
  ASSERT_DOUBLE_EQ(105. / 532, b.GetElement(2, 3));
  EXPECT_TRUE(a_inverse == b);
}

TEST(MatrixTests, CalculateInverseOfAnotherMatrix) {
  Matrix a({{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}});
  Matrix a_inverse({{90. / -585, 90. / -585, 165. / -585, 315. / -585},
                    {45. / -585, -72. / -585, -15. / -585, -18. / -585},
                    {-210. / -585, -210. / -585, -255. / -585, -540. / -585},
                    {405. / -585, 405. / -585, 450. / -585, 1125. / -585}});
  Matrix b = a.Inverse();
  EXPECT_TRUE(a_inverse == b);
}

TEST(MatrixTests, CalculateInverseOfYetAnotherMatrix) {
  Matrix a({{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}});
  Matrix a_inverse({{-66. / 1620, -126. / 1620, 234. / 1620, -360. / 1620},
                    {-126. / 1620, 54. / 1620, 594. / 1620, -540. / 1620},
                    {-47. / 1620, -237. / 1620, -177. / 1620, 210. / 1620},
                    {288. / 1620, 108. / 1620, -432. / 1620, 540. / 1620}});
  Matrix b = a.Inverse();
  EXPECT_TRUE(a_inverse == b);
}

TEST(MatrixTests, MultiplyMatrixByItsInverse) {
  Matrix a({{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}});
  Matrix b({{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}});
  Matrix c = a * b;
  EXPECT_TRUE(a == c * b.Inverse());
}

TEST(MatrixTests, MultiplyByTranslationMatrix) {
  Translation transform(5, -3, 2);
  Point point(-3, 4, 5);
  EXPECT_TRUE(Point(2, 1, 7) == transform * point);
}

TEST(MatrixTests, MultiplyByInverseOfTranslation) {
  Translation transform(5, -3, 2);
  Matrix inverse = transform.Inverse();
  Point point(-3, 4, 5);
  EXPECT_TRUE(Point(-8, 7, 3) == inverse * point);
}

TEST(MatrixTests, TranslationDoesNotAffectVectors) {
  Translation transform(5, -3, 2);
  Vector vector(-3, 4, 5);
  EXPECT_TRUE(vector == transform * vector);
}

TEST(MatrixTests, ScalingAppliedToPoint) {
  Scaling transform(2, 3, 4);
  Point point(-4, 6, 8);
  EXPECT_TRUE(Point(-8, 18, 32) == transform * point);
}

TEST(MatrixTests, ScalingAppliedToVector) {
  Scaling transform(2, 3, 4);
  Vector vector(-4, 6, 8);
  EXPECT_TRUE(Vector(-8, 18, 32) == transform * vector);
}

TEST(MatrixTests, MultiplyByInverseOfScalingMatrix) {
  Scaling transform(2, 3, 4);
  Matrix inverse = transform.Inverse();
  Vector vector(-4, 6, 8);
  EXPECT_TRUE(Vector(-2, 2, 2) == inverse * vector);
}

TEST(MatrixTests, ReflectionIsScalingByNegativeValue) {
  Scaling transform(-1, 1, 1);
  Point point(2, 3, 4);
  EXPECT_TRUE(Point(-2, 3, 4) == transform * point);
}

TEST(MatrixTests, RotatePointAroundXAxis) {
  Point point(0, 1, 0);
  RotationX half_quarter(M_PI / 4);
  RotationX full_quarter(M_PI / 2);
  EXPECT_TRUE(Point(0, sqrt(2) / 2, sqrt(2) / 2) == half_quarter * point);
  EXPECT_TRUE(Point(0, 0, 1) == full_quarter * point);
}

TEST(MatrixTests, InverseOfXRotationRotatesInOppositeDirection) {
  Point point(0, 1, 0);
  RotationX half_quarter(M_PI / 4);
  Matrix inverse = half_quarter.Inverse();
  EXPECT_TRUE(Point(0, sqrt(2) / 2, -sqrt(2) / 2) == inverse * point);
}

TEST(MatrixTests, RotatePointAroundYAxis) {
  Point point(0, 0, 1);
  RotationY half_quarter(M_PI / 4);
  RotationY full_quarter(M_PI / 2);
  EXPECT_TRUE(Point(sqrt(2) / 2, 0, sqrt(2) / 2) == half_quarter * point);
  EXPECT_TRUE(Point(1, 0, 0) == full_quarter * point);
}

TEST(MatrixTests, RotatePointAroundZAxis) {
  Point point(0, 1, 0);
  RotationZ half_quarter(M_PI / 4);
  RotationZ full_quarter(M_PI / 2);
  EXPECT_TRUE(Point(-sqrt(2) / 2, sqrt(2) / 2, 0) == half_quarter * point);
  EXPECT_TRUE(Point(-1, 0, 0) == full_quarter * point);
}

TEST(MatrixTests, ShearingTransformationMovesXInProportionToY) {
  Shearing transform(1, 0, 0, 0, 0, 0);
  Point point(2, 3, 4);
  EXPECT_TRUE(Point(5, 3, 4) == transform * point);
}

TEST(MatrixTests, ShearingTransformationMovesXInProportionToZ) {
  Shearing transform(0, 1, 0, 0, 0, 0);
  Point point(2, 3, 4);
  EXPECT_TRUE(Point(6, 3, 4) == transform * point);
}

TEST(MatrixTests, ShearingTransformationMovesYInProportionToX) {
  Shearing transform(0, 0, 1, 0, 0, 0);
  Point point(2, 3, 4);
  EXPECT_TRUE(Point(2, 5, 4) == transform * point);
}

TEST(MatrixTests, ShearingTransformationMovesYInProportionToZ) {
  Shearing transform(0, 0, 0, 1, 0, 0);
  Point point(2, 3, 4);
  EXPECT_TRUE(Point(2, 7, 4) == transform * point);
}

TEST(MatrixTests, ShearingTransformationMovesZInProportionToX) {
  Shearing transform(0, 0, 0, 0, 1, 0);
  Point point(2, 3, 4);
  EXPECT_TRUE(Point(2, 3, 6) == transform * point);
}

TEST(MatrixTests, ShearingTransformationMovesZInProportionToY) {
  Shearing transform(0, 0, 0, 0, 0, 1);
  Point point(2, 3, 4);
  EXPECT_TRUE(Point(2, 3, 7) == transform * point);
}

TEST(MatrixTests, IndividualTransformationsAreAppliedInSequence) {
  RotationX a(M_PI / 2);
  Scaling b(5, 5, 5);
  Translation c(10, 5, 7);
  Point point(1, 0, 1);

  Point p2 = a * point;
  EXPECT_TRUE(Point(1, -1, 0) == p2);

  Point p3 = b * p2;
  EXPECT_TRUE(Point(5, -5, 0) == p3);

  Point p4 = c * p3;
  EXPECT_TRUE(Point(15, 0, 7) == p4);
}

TEST(MatrixTests, ChainedTransformationsMustBeAppliedInReverseOrder) {
  Identity transform =
      Identity().RotateX(M_PI / 2).Scale(5, 5, 5).Translate(10, 5, 7);
  Point point(1, 0, 1);
  EXPECT_TRUE(Point(15, 0, 7) == transform * point);
}

TEST(MatrixTests, TransformationMatrixForDefaultOrientation) {
  Point from(0, 0, 0);
  Point to(0, 0, -1);
  Vector up(0, 1, 0);
  Matrix t = ViewTransform(from, to, up);
  EXPECT_TRUE(Identity() == t);
}

TEST(MatrixTests, ViewTransformationMatrixLookingInPositiveZDirection) {
  Point from(0, 0, 0);
  Point to(0, 0, 1);
  Vector up(0, 1, 0);
  Matrix t = ViewTransform(from, to, up);
  EXPECT_TRUE(Scaling(-1, 1, -1) == t);
}

TEST(MatrixTests, ViewTransformationMoveTheWorld) {
  Point from(0, 0, 8);
  Point to(0, 0, 0);
  Vector up(0, 1, 0);
  Matrix t = ViewTransform(from, to, up);
  EXPECT_TRUE(Translation(0, 0, -8) == t);
}

TEST(MatrixTests, ArbitraryViewTransformation) {
  Point from(1, 3, 2);
  Point to(4, -2, 8);
  Vector up(1, 1, 0);
  Matrix t = ViewTransform(from, to, up);
  EXPECT_TRUE(Matrix({{-0.50709255283710986, 0.50709255283710986,
                       0.67612340378281321, -2.3664319132398459},
                      {0.76771593385968007, 0.60609152673132627,
                       0.12121830534626524, -2.8284271247461894},
                      {-0.35856858280031806, 0.59761430466719678,
                       -0.71713716560063612, 0},
                      {0, 0, 0, 1}}) == t);
}
