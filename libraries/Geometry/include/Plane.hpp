#pragma once

#include "Shape.hpp"

namespace raytracer {
namespace geometry {

class Plane : public Shape {
public:
  Plane() : Shape() {}

  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);
  Bounds ComputeBounds();
};

} // namespace geometry
} // namespace raytracer
