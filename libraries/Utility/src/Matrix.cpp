#include "Matrix.h"

#include <numeric>

using namespace raytracer;

Matrix Matrix::Transpose() {
  Matrix result(columns_, rows_);

  for (size_t row = 0; row < rows_; ++row) {
    for (size_t column = 0; column < columns_; ++column) {
      result(row, column) = GetElement(column, row);
    }
  }
  return result;
}

std::ostream &operator<<(std::ostream &os, const raytracer::Matrix &m) {
  for (size_t row = 0; row < m.rows_; ++row) {
    os << m.GetElement(row, 0) << " " << m.GetElement(row, 1) << " "
       << m.GetElement(row, 2) << " " << m.GetElement(row, 3) << std::endl;
  }
  return os;
}

bool operator==(const Matrix &m1, const Matrix &m2) {
  if (m1.rows_ != m2.rows_ || m1.columns_ != m2.rows_) {
    return false;
  }

  for (size_t row = 0; row < m1.rows_; ++row) {
    for (size_t column = 0; column < m1.columns_; ++column) {
      if (!AlmostEquals(m1.GetElement(row, column),
                        m2.GetElement(row, column))) {
        return false;
      }
    }
  }
  return true;
}

bool operator!=(const Matrix &m1, const Matrix &m2) { return !(m1 == m2); }

raytracer::Matrix operator*(const raytracer::Matrix &m1,
                            const raytracer::Matrix &m2) {
  assert(m1.columns_ == m2.rows_);

  raytracer::Matrix result(m1.rows_, m2.columns_);
  std::vector<double> row_column_multiplications(m1.columns_);

  for (size_t row = 0; row < m1.rows_; ++row) {
    for (size_t column = 0; column < m2.columns_; ++column) {
      for (size_t k = 0; k < m1.columns_; ++k) {
        row_column_multiplications[k] =
            m1.GetElement(row, k) * m2.GetElement(k, column);
      }
      result(row, column) =
          std::accumulate(row_column_multiplications.begin(),
                          row_column_multiplications.end(), 0.0);
    }
  }

  return result;
}

raytracer::Tuple operator*(const raytracer::Matrix &m,
                           const raytracer::Tuple &t) {
  assert(m.rows_ == 4);

  raytracer::Tuple result(0, 0, 0, 0);
  for (size_t row = 0; row < m.rows_; ++row) {
    result.e[row] = m.GetElement(row, 0) * t[0] + m.GetElement(row, 1) * t[1] +
                    m.GetElement(row, 2) * t[2] + m.GetElement(row, 3) * t[3];
  }
  return result;
}
