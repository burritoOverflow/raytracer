#pragma once

#include <vector>

#include "Material.h"
#include "Matrix.h"
#include "Point.h"
#include "Ray.h"

namespace raytracer {
namespace geometry {

class Sphere {
public:
  Sphere()
      : id_(ID++), origin_(utility::Point(0, 0, 0)), radii_(1),
        transform_(utility::Identity()), material_(material::Material()) {}

  double Discriminant(utility::Ray ray);

  void SetTransform(utility::Matrix transform);
  utility::Vector NormalAt(utility::Point point);

  static std::atomic<uint64_t> ID;

  uint64_t id_;
  utility::Point origin_;
  double radii_;
  utility::Matrix transform_;
  material::Material material_;
};

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Sphere &s1,
                const raytracer::geometry::Sphere &s2);