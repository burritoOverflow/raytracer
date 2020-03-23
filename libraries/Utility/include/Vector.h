#pragma once

#include "Tuple.h"

namespace raytracer {
namespace utility {

class Vector : public Tuple {
public:
  Vector() : Tuple() {}
  Vector(double e0, double e1, double e2) : Tuple(e0, e1, e2, 0.0) {}
  Vector(const Tuple &t) : Tuple(t) {}

  inline Vector Cross(const Vector &v) {
    return Vector(y() * v.z() - z() * v.y(), z() * v.x() - x() * v.z(),
                  x() * v.y() - y() * v.x());
  }

  inline Vector Reflect(const Vector &normal) {
    return (*this) - normal * 2 * (*this).Dot(normal);
  }
};

} // namespace utility
} // namespace raytracer
