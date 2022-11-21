#pragma once

#include "Shape.h"

#include <utility>

namespace raytracer {
namespace geometry {

class Cube : public Shape {
public:
  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);

private:
  std::tuple<double, double> CheckAxis(double origin, double direction);
};

} // namespace geometry
} // namespace raytracer