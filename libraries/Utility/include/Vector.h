#pragma once

#include "Tuple.h"

namespace raytracer {
class Vector : public Tuple {
public:
  Vector() : Tuple() {}
  Vector(double e0, double e1, double e2) : Tuple(e0, e1, e2, 0.0) {}
  Vector(const Tuple &t) : Tuple(t) {}

  inline Vector cross(const Vector &v) {
    return Vector(y() * v.z() - z() * v.y(), z() * v.x() - x() * v.z(),
                  x() * v.y() - y() * v.x());
  }
};
} // namespace raytracer
