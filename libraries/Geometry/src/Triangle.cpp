#include "Triangle.hpp"

#include <algorithm>

namespace raytracer {
namespace geometry {

std::vector<Intersection> Triangle::LocalIntersect(utility::Ray &ray) {
  auto dir_cross_e2 = ray.direction_.Cross(e2_);
  double determinant = e1_.Dot(dir_cross_e2);
  if (std::abs(determinant) < EPSILON) {
    return {};
  }

  double f = 1.0 / determinant;
  utility::Vector p1_to_origin = ray.origin_ - p1_;
  double u = f * p1_to_origin.Dot(dir_cross_e2);
  if (u < 0 || u > 1) {
    return {};
  }

  auto origin_cross_e1 = p1_to_origin.Cross(e1_);
  double v = f * ray.direction_.Dot(origin_cross_e1);
  if (v < 0 || (u + v) > 1) {
    return {};
  }

  double t = f * e2_.Dot(origin_cross_e1);
  return std::vector<Intersection>{
      Intersection(t, std::make_shared<Triangle>(*this))};
}

utility::Vector Triangle::LocalNormalAt(utility::Point &point) {
  return normal_;
}

Bounds Triangle::ComputeBounds() {
  return Bounds(utility::Point(std::min({p1_.x(), p2_.x(), p3_.x()}),
                               std::min({p1_.y(), p2_.y(), p3_.y()}),
                               std::min({p1_.z(), p2_.z(), p3_.z()})),
                utility::Point(std::max({p1_.x(), p2_.x(), p3_.x()}),
                               std::max({p1_.y(), p2_.y(), p3_.y()}),
                               std::max({p1_.z(), p2_.z(), p3_.z()})));
}

} // namespace geometry
} // namespace raytracer