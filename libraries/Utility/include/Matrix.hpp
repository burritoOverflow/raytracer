#pragma once

#include <cassert>
#include <cmath>
#include <vector>

#include "AlmostEquals.hpp"
#include "Point.hpp"
#include "Tuple.hpp"
#include "Vector.hpp"

namespace raytracer {
namespace utility {

class Matrix {
public:
  Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns) {
    matrix_.resize(rows, std::vector<double>(columns));
    for (size_t row = 0; row < rows; ++row) {
      for (size_t column = 0; column < columns; ++column) {
        matrix_[row][column] = 0;
      }
    }
  }
  Matrix(size_t rows, size_t columns, std::vector<std::vector<double>> matrix)
      : rows_(rows), columns_(columns), matrix_(matrix) {}
  Matrix(std::vector<std::vector<double>> matrix) : matrix_(matrix) {
    rows_ = matrix_.size();
    columns_ = matrix_[0].size();
  }
  ~Matrix() {}

  inline double &operator()(size_t row, size_t column) {
    assert(row >= 0 && row < rows_);
    assert(column >= 0 && column < columns_);
    return matrix_[row][column];
  }

  inline double GetElement(size_t row, size_t column) const {
    assert(row >= 0 && row < rows_);
    assert(column >= 0 && column < columns_);
    return matrix_[row][column];
  }

  Matrix Transpose();

  double Determinant();
  Matrix Submatrix(size_t row, size_t column);
  double Minor(size_t row, size_t column);
  double Cofactor(size_t row, size_t column);

  bool IsInvertible();
  Matrix Inverse();

  Matrix Translate(double x, double y, double z);
  Matrix Scale(double x, double y, double z);
  Matrix RotateX(double radians);
  Matrix RotateY(double radians);
  Matrix RotateZ(double radians);
  Matrix Shear(double x_y, double x_z, double y_x, double y_z, double z_x,
               double z_y);

  size_t rows_;
  size_t columns_;
  std::vector<std::vector<double>> matrix_;
};

class Identity : public Matrix {
public:
  Identity() : Matrix(4, 4) {
    for (size_t i = 0; i < 4; ++i) {
      (*this)(i, i) = 1;
    }
  }
  Identity(const Matrix &m) : Matrix(m) {}
};

class Translation : public Identity {
public:
  Translation(double x, double y, double z) : Identity() {
    (*this)(0, 3) = x;
    (*this)(1, 3) = y;
    (*this)(2, 3) = z;
  }
  Translation(const Identity &m) : Identity(m) {}
};

class Scaling : public Matrix {
public:
  Scaling(double x, double y, double z) : Matrix(4, 4) {
    (*this)(0, 0) = x;
    (*this)(1, 1) = y;
    (*this)(2, 2) = z;
    (*this)(3, 3) = 1;
  }
  Scaling(const Matrix &m) : Matrix(m) {}
};

/* The rotation matrices obeys the left-hand rule */
class RotationX : public Matrix {
public:
  RotationX(double radians) : Matrix(4, 4) {
    (*this)(0, 0) = 1;
    (*this)(1, 1) = cos(radians);
    (*this)(1, 2) = -sin(radians);
    (*this)(2, 1) = sin(radians);
    (*this)(2, 2) = cos(radians);
    (*this)(3, 3) = 1;
  }
  RotationX(const Matrix &m) : Matrix(m) {}
};

class RotationY : public Matrix {
public:
  RotationY(double radians) : Matrix(4, 4) {
    (*this)(0, 0) = cos(radians);
    (*this)(0, 2) = sin(radians);
    (*this)(1, 1) = 1;
    (*this)(2, 0) = -sin(radians);
    (*this)(2, 2) = cos(radians);
    (*this)(3, 3) = 1;
  }
  RotationY(const Matrix &m) : Matrix(m) {}
};

class RotationZ : public Matrix {
public:
  RotationZ(double radians) : Matrix(4, 4) {
    (*this)(0, 0) = cos(radians);
    (*this)(0, 1) = -sin(radians);
    (*this)(1, 0) = sin(radians);
    (*this)(1, 1) = cos(radians);
    (*this)(2, 2) = 1;
    (*this)(3, 3) = 1;
  }
  RotationZ(const Matrix &m) : Matrix(m) {}
};

class Shearing : public Identity {
public:
  Shearing(double x_y, double x_z, double y_x, double y_z, double z_x,
           double z_y)
      : Identity() {
    (*this)(0, 1) = x_y;
    (*this)(0, 2) = x_z;
    (*this)(1, 0) = y_x;
    (*this)(1, 2) = y_z;
    (*this)(2, 0) = z_x;
    (*this)(2, 1) = z_y;
  }
  Shearing(const Identity &m) : Identity(m) {}
};

Matrix ViewTransform(Point from, Point to, Vector up);

} // namespace utility
} // namespace raytracer

std::ostream &operator<<(std::ostream &os, const raytracer::utility::Matrix &m);

bool operator==(const raytracer::utility::Matrix &m1,
                const raytracer::utility::Matrix &m2);
bool operator!=(const raytracer::utility::Matrix &m1,
                const raytracer::utility::Matrix &m2);
raytracer::utility::Matrix operator*(const raytracer::utility::Matrix &m1,
                                     const raytracer::utility::Matrix &m2);
raytracer::utility::Tuple operator*(const raytracer::utility::Matrix &m,
                                    const raytracer::utility::Tuple &t);