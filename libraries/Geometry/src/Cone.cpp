#include "Cone.hpp"

#include <algorithm>
#include <cmath>

namespace raytracer {
namespace geometry {

std::vector<Intersection> Cone::LocalIntersect(utility::Ray &ray) {
  double a = std::pow(ray.direction_.x(), 2) - std::pow(ray.direction_.y(), 2) +
             std::pow(ray.direction_.z(), 2);
  double b = 2 * (ray.origin_.x() * ray.direction_.x() -
                  ray.origin_.y() * ray.direction_.y() +
                  ray.origin_.z() * ray.direction_.z());
  double c = std::pow(ray.origin_.x(), 2) - std::pow(ray.origin_.y(), 2) +
             std::pow(ray.origin_.z(), 2);

  std::vector<Intersection> xs;
  if (AlmostEquals(a, 0)) {
    if (AlmostEquals(b, 0)) {
      return xs;
    } else {
      xs.emplace_back(
          Intersection(-c / (2 * b), std::make_shared<Cone>(*this)));
      IntersectCaps(ray, xs);
      return xs;
    }
  }

  auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return {};
  }

  double t0 = (-b - sqrt(discriminant)) / (2 * a);
  double t1 = (-b + sqrt(discriminant)) / (2 * a);
  if (t0 > t1) {
    std::swap(t0, t1);
  }

  auto y0 = ray.origin_.y() + t0 * ray.direction_.y();
  if (minimum_ < y0 && y0 < maximum_) {
    xs.emplace_back(Intersection(t0, std::make_shared<Cone>(*this)));
  }
  auto y1 = ray.origin_.y() + t1 * ray.direction_.y();
  if (minimum_ < y1 && y1 < maximum_) {
    xs.emplace_back(Intersection(t1, std::make_shared<Cone>(*this)));
  }
  IntersectCaps(ray, xs);

  return xs;
}

utility::Vector Cone::LocalNormalAt(utility::Point &point) {
  // Compute the square of the distance from the y axis.
  double y = std::sqrt(std::pow(point.x(), 2) + std::pow(point.z(), 2));
  if (point.y() > 0) {
    y = -y;
  }

  if (y < 1 && point.y() >= maximum_ - EPSILON) {
    return utility::Vector(0, 1, 0);
  } else if (y < 1 && point.y() <= minimum_ + EPSILON) {
    return utility::Vector(0, -1, 0);
  } else {
    return utility::Vector(point.x(), y, point.z());
  }
}

bool Cone::CheckCap(const utility::Ray ray, double t, double radius) {
  double x = ray.origin_.x() + t * ray.direction_.x();
  double z = ray.origin_.z() + t * ray.direction_.z();
  return (x * x + z * z) <= radius + EPSILON;
}

void Cone::IntersectCaps(const utility::Ray ray,
                         std::vector<Intersection> &xs) {
  if (!closed_ || AlmostEquals(ray.direction_.y(), 0)) {
    return;
  }

  double t = (minimum_ - ray.origin_.y()) / ray.direction_.y();
  if (CheckCap(ray, t, std::abs(minimum_))) {
    xs.emplace_back(Intersection(t, std::make_shared<Cone>(*this)));
  }

  t = (maximum_ - ray.origin_.y()) / ray.direction_.y();
  if (CheckCap(ray, t, std::abs(maximum_))) {
    xs.emplace_back(Intersection(t, std::make_shared<Cone>(*this)));
  }
}

} // namespace geometry
} // namespace raytracer