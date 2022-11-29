#pragma once

#include "Shape.hpp"

#include <utility>

namespace raytracer {
namespace geometry {

class Cube : public Shape {
public:
  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);
  Bounds ComputeBounds();
};

} // namespace geometry
} // namespace raytracer