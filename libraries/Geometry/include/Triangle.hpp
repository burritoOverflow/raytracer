#pragma once

#include "Shape.hpp"

namespace raytracer {
namespace geometry {

class Triangle : public Shape {
public:
  Triangle(utility::Point p1, utility::Point p2, utility::Point p3)
      : p1_(p1), p2_(p2), p3_(p3) {
    e1_ = p2 - p1;
    e2_ = p3 - p1;
    normal_ = e2_.Cross(e1_).Normalize();
  }

  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);
  Bounds ComputeBounds();

  utility::Point p1_, p2_, p3_;
  utility::Vector e1_, e2_;
  utility::Vector normal_;
};

} // namespace geometry
} // namespace raytracer
