#pragma once

#include "Shape.hpp"

namespace raytracer {
namespace geometry {

class Group : public Shape {
public:
  void AddChild(std::shared_ptr<Shape> child);

  std::vector<Intersection> LocalIntersect(utility::Ray &ray);
  utility::Vector LocalNormalAt(utility::Point &point);
  Bounds ComputeBounds() { return bounds_; }

  std::vector<std::shared_ptr<Shape>> children_;
  Bounds bounds_ =
      Bounds(utility::Point(-std::numeric_limits<double>::infinity(),
                            -std::numeric_limits<double>::infinity(),
                            -std::numeric_limits<double>::infinity()),
             utility::Point(std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::infinity(),
                            std::numeric_limits<double>::infinity()));

private:
  void ExtendBounds(std::shared_ptr<Shape> &shape);
  bool IntersectsBounds(utility::Ray &ray);
};

} // namespace geometry
} // namespace raytracer
