#pragma once

#include "Matrix.h"
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

Ray Transform(Ray &r, Matrix &m);

} // namespace utility
} // namespace raytracer

raytracer::utility::Ray operator*(const raytracer::utility::Matrix &m,
                                  const raytracer::utility::Ray &r);
