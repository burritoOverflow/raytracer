#pragma once

#include <initializer_list>
#include <vector>

#include "Sphere.h"

namespace raytracer {
namespace geometry {

class Intersection {
public:
  Intersection(double t, Sphere sphere)
      : t_(t), object_(sphere) {} // TODO: Generalize for all kinds of objects

  double t_;
  Sphere object_;
};

std::vector<Intersection> Intersect(Sphere &sphere, utility::Ray ray);
std::vector<Intersection>
Intersections(const std::initializer_list<Intersection> &intersections);

} // namespace geometry
} // namespace raytracer