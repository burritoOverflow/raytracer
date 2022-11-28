#include "Group.hpp"

#include <algorithm>

namespace raytracer {
namespace geometry {

void Group::AddChild(std::shared_ptr<Shape> child) {
  child->parent_ = this;
  children_.push_back(child);
}

std::vector<Intersection> Group::LocalIntersect(utility::Ray &ray) {
  std::vector<Intersection> intersections;
  for (auto &child : children_) {
    auto xs = child->Intersect(ray);
    intersections.insert(intersections.end(), xs.begin(), xs.end());
  }
  std::sort(intersections.begin(), intersections.end(),
            [](const auto &i1, const auto &i2) { return i1.t_ < i2.t_; });

  return intersections;
}

utility::Vector Group::LocalNormalAt(utility::Point &point) {
  throw std::domain_error("Group::localNormalAt cannot be called");
}

} // namespace geometry
} // namespace raytracer