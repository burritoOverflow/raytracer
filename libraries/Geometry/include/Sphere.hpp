#pragma once

#include "Shape.hpp"

namespace raytracer {
namespace geometry {

class Sphere : public Shape {
public:
  Sphere() : Shape(), origin_(utility::Point(0, 0, 0)), radii_(1) {}

  double Discriminant(utility::Ray ray);
  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);

  utility::Point origin_;
  double radii_;
};

Sphere GlassSphere();

} // namespace geometry
} // namespace raytracer
