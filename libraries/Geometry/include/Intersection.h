#pragma once

#include <initializer_list>
#include <optional>
#include <vector>

#include "Sphere.h"

namespace raytracer {
namespace geometry {

class Intersection {
public:
  Intersection(double t, Sphere &sphere)
      : t_(t), object_(sphere) {} // TODO: Generalize for all kinds of objects

  double t_;
  Sphere object_;
};

std::vector<Intersection> Intersect(Sphere &sphere, utility::Ray ray);
std::vector<Intersection>
Intersections(const std::initializer_list<Intersection> &intersections);
std::optional<Intersection> Hit(std::vector<Intersection> &intersections);

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Intersection &i1,
                const raytracer::geometry::Intersection &i2);
bool operator!=(const raytracer::geometry::Intersection &i1,
                const raytracer::geometry::Intersection &i2);