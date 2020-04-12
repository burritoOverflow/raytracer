#pragma once

#include <vector>

#include "Material.h"
#include "Matrix.h"
#include "Point.h"
#include "Ray.h"
#include "Shape.h"

namespace raytracer {
namespace geometry {

class Sphere : public Shape {
public:
  Sphere() : Shape(), origin_(utility::Point(0, 0, 0)), radii_(1) {}

  double Discriminant(utility::Ray ray);

  utility::Vector NormalAt(utility::Point point);

  static std::atomic<uint64_t> ID;

  utility::Point origin_;
  double radii_;
};

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Sphere &s1,
                const raytracer::geometry::Sphere &s2);