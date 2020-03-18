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
  std::vector<double> Intersect(utility::Ray ray);

  static std::atomic<uint64_t> ID;

  uint64_t id_;
  utility::Point origin_;
  double radii_;
};

std::atomic<uint64_t> Sphere::ID = 0;

} // namespace geometry
} // namespace raytracer
