#pragma once

#include <vector>

#include "Point.h"
#include "Ray.h"

namespace raytracer {
namespace geometry {

class Sphere {
public:
  Sphere() : id_(ID++), origin_(utility::Point(0, 0, 0)), radii_(1) {}

  double Discriminant(utility::Ray ray);

  static std::atomic<uint64_t> ID;

  uint64_t id_;
  utility::Point origin_;
  double radii_;
};

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Sphere &s1,
                const raytracer::geometry::Sphere &s2);