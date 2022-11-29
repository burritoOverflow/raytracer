#include "Group.hpp"

#include <algorithm>

namespace raytracer {
namespace geometry {

void Group::AddChild(std::shared_ptr<Shape> child) {
  child->parent_ = this;
  children_.push_back(child);
}

std::vector<Intersection> Group::LocalIntersect(utility::Ray &ray) {
  if (!IntersectsBounds(ray)) {
    return {};
  }

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

void Group::ExtendBounds(std::shared_ptr<Shape> &shape) {
  bounds_.Merge(shape->ComputeBounds().Transform(shape->transform_));
}

bool Group::IntersectsBounds(utility::Ray &ray) {
  auto [xtmin, xtmax] = CheckAxis(ray.origin_.x(), ray.direction_.x(),
                                  bounds_.minimum_.x(), bounds_.maximum_.x());
  auto [ytmin, ytmax] = CheckAxis(ray.origin_.y(), ray.direction_.y(),
                                  bounds_.minimum_.y(), bounds_.maximum_.y());
  auto [ztmin, ztmax] = CheckAxis(ray.origin_.z(), ray.direction_.z(),
                                  bounds_.minimum_.z(), bounds_.maximum_.z());

  auto tmin = std::max({xtmin, ytmin, ztmin});
  auto tmax = std::min({xtmax, ytmax, ztmax});

  return tmin < tmax;
}

} // namespace geometry
} // namespace raytracer
