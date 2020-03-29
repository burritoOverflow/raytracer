#include "Matrix.h"

#include <numeric>

namespace raytracer {
namespace utility {

Matrix Matrix::Transpose() {
  Matrix result(columns_, rows_);

  for (size_t row = 0; row < rows_; ++row) {
    for (size_t column = 0; column < columns_; ++column) {
      result(row, column) = GetElement(column, row);
    }
  }
  return result;
}

double Matrix::Determinant() {
  double determinant = 0;

  if (rows_ == 2 && columns_ == 2) {
    determinant = GetElement(0, 0) * GetElement(1, 1) -
                  GetElement(1, 0) * GetElement(0, 1);
  }

  for (size_t column = 0; column < columns_; ++column) {
    determinant += GetElement(0, column) * Cofactor(0, column);
  }

  return determinant;
}

/* Removes the specified row and column from the matrix */
Matrix Matrix::Submatrix(size_t row, size_t column) {
  Matrix result(rows_ - 1, columns_ - 1);

  for (size_t r = 0; r < rows_; ++r) {
    if (r == row) {
      continue;
    }
    for (size_t c = 0; c < columns_; ++c) {
      if (c == column) {
        continue;
      }
      size_t row_index = r >= row ? r - 1 : r;
      size_t column_index = c >= column ? c - 1 : c;
      result(row_index, column_index) = GetElement(r, c);
    }
  }
  return result;
}

double Matrix::Minor(size_t row, size_t column) {
  return Submatrix(row, column).Determinant();
}

double Matrix::Cofactor(size_t row, size_t column) {
  double minor = Minor(row, column);
  return (row + column) % 2 ? -minor : minor;
}

bool Matrix::IsInvertible() { return !AlmostEquals(0, Determinant()); }

Matrix Matrix::Inverse() {
  assert(IsInvertible());

  Matrix result(rows_, columns_);
  double cofactor = 0;
  double determinant = Determinant();
  for (size_t row = 0; row < rows_; ++row) {
    for (size_t column = 0; column < columns_; ++column) {
      cofactor = Cofactor(row, column);
      result(column, row) = cofactor / determinant;
    }
  }
  return result;
}

Matrix Matrix::Translate(double x, double y, double z) {
  Translation translation(x, y, z);
  return translation * (*this);
}

Matrix Matrix::Scale(double x, double y, double z) {
  Scaling scaling(x, y, z);
  return scaling * (*this);
}

Matrix Matrix::RotateX(double radians) {
  RotationX rotation(radians);
  return rotation * (*this);
}

Matrix Matrix::RotateY(double radians) {
  RotationY rotation(radians);
  return rotation * (*this);
}

Matrix Matrix::RotateZ(double radians) {
  RotationZ rotation(radians);
  return rotation * (*this);
}

Matrix Matrix::Shear(double x_y, double x_z, double y_x, double y_z, double z_x,
                     double z_y) {
  Shearing shearing(x_y, x_z, y_x, y_z, z_x, z_y);
  return shearing * (*this);
}

Matrix ViewTransform(Point from, Point to, Vector up) {
  utility::Vector forward = (to - from).Normalize();
  utility::Vector left = forward.Cross(up.Normalize());
  utility::Vector true_up = left.Cross(forward);

  utility::Matrix orientation({{left.x(), left.y(), left.z(), 0},
                               {true_up.x(), true_up.y(), true_up.z(), 0},
                               {-forward.x(), -forward.y(), -forward.z(), 0},
                               {0, 0, 0, 1}});

  return orientation * Translation(-from.x(), -from.y(), -from.z());
}

} // namespace utility
} // namespace raytracer

std::ostream &operator<<(std::ostream &os,
                         const raytracer::utility::Matrix &m) {
  for (size_t row = 0; row < m.rows_; ++row) {
    for (size_t column = 0; column < m.columns_; ++column) {
      os << m.GetElement(row, column);
      if (column != m.columns_ - 1) {
        os << " ";
      }
    }
    os << std::endl;
  }
  return os;
}

bool operator==(const raytracer::utility::Matrix &m1,
                const raytracer::utility::Matrix &m2) {
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

bool operator!=(const raytracer::utility::Matrix &m1,
                const raytracer::utility::Matrix &m2) {
  return !(m1 == m2);
}

raytracer::utility::Matrix operator*(const raytracer::utility::Matrix &m1,
                                     const raytracer::utility::Matrix &m2) {
  assert(m1.columns_ == m2.rows_);

  raytracer::utility::Matrix result(m1.rows_, m2.columns_);
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

raytracer::utility::Tuple operator*(const raytracer::utility::Matrix &m,
                                    const raytracer::utility::Tuple &t) {
  assert(m.rows_ == 4);

  raytracer::utility::Tuple result(0, 0, 0, 0);
  for (size_t row = 0; row < m.rows_; ++row) {
    result.e[row] = m.GetElement(row, 0) * t[0] + m.GetElement(row, 1) * t[1] +
                    m.GetElement(row, 2) * t[2] + m.GetElement(row, 3) * t[3];
  }
  return result;
}
