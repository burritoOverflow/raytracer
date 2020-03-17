#pragma once

#include "Point.h"
#include "Vector.h"

namespace raytracer {
namespace utility {

class Ray {
public:
  Ray(Point origin, Vector direction)
      : origin_(origin), direction_(direction) {}

  Point Position(double t) { return origin_ + direction_ * t; }

  Point origin_;
  Vector direction_;
};

} // namespace utility
} // namespace raytracer
