#pragma once

#include <vector>

#include "AlmostEquals.h"
#include "Tuple.h"

namespace raytracer {
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

  size_t rows_;
  size_t columns_;
  std::vector<std::vector<double>> matrix_;
};
} // namespace raytracer

std::ostream &operator<<(std::ostream &os, const raytracer::Matrix &m);

bool operator==(const raytracer::Matrix &m1, const raytracer::Matrix &m2);
bool operator!=(const raytracer::Matrix &m1, const raytracer::Matrix &m2);
raytracer::Matrix operator*(const raytracer::Matrix &m1,
                            const raytracer::Matrix &m2);
raytracer::Tuple operator*(const raytracer::Matrix &m,
                           const raytracer::Tuple &t);
