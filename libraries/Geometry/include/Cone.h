#pragma once

#include "Shape.h"

#include <utility>

namespace raytracer {
namespace geometry {

class Cone : public Shape {
public:
  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);

  double minimum_ = -std::numeric_limits<double>::infinity();
  double maximum_ = std::numeric_limits<double>::infinity();
  bool closed_ = false;

private:
  bool CheckCap(const utility::Ray ray, double t, double radius);
  void IntersectCaps(const utility::Ray ray, std::vector<Intersection> &xs);
};

} // namespace geometry
} // namespace raytracer