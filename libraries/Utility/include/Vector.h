#pragma once

#include "Tuple.h"

namespace raytracer {
class Vector : public Tuple {
public:
  Vector() : Tuple() {}
  Vector(double e0, double e1, double e2) : Tuple(e0, e1, e2, 0.0) {}

  inline Vector cross(const Vector &v) {
    return Vector(this->y() * v.z() - this->z() * v.y(),
                  this->z() * v.x() - this->x() * v.z(),
                  this->x() * v.y() - this->y() * v.x());
  }
};
} // namespace raytracer