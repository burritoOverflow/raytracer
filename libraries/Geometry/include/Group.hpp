#pragma once

#include "Shape.hpp"

namespace raytracer {
namespace geometry {

class Group : public Shape {
public:
  void AddChild(std::shared_ptr<Shape> child);

  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);

  std::vector<std::shared_ptr<Shape>> children_;
};

} // namespace geometry
} // namespace raytracer
