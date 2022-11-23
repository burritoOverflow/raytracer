#include "Cylinder.hpp"

#include <algorithm>
#include <cmath>

namespace raytracer {
namespace geometry {

std::vector<Intersection> Cylinder::LocalIntersect(utility::Ray &ray) {
  double a = std::pow(ray.direction_.x(), 2) + std::pow(ray.direction_.z(), 2);

  std::vector<Intersection> xs;
  if (AlmostEquals(a, 0)) {
    IntersectCaps(ray, xs);
    return xs;
  }

  double b = 2 * (ray.origin_.x() * ray.direction_.x() +
                  ray.origin_.z() * ray.direction_.z());
  double c = std::pow(ray.origin_.x(), 2) + std::pow(ray.origin_.z(), 2) - 1;

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
    xs.emplace_back(Intersection(t0, std::make_shared<Cylinder>(*this)));
  }
  auto y1 = ray.origin_.y() + t1 * ray.direction_.y();
  if (minimum_ < y1 && y1 < maximum_) {
    xs.emplace_back(Intersection(t1, std::make_shared<Cylinder>(*this)));
  }
  IntersectCaps(ray, xs);

  return xs;
}

utility::Vector Cylinder::LocalNormalAt(utility::Point &point) {
  // Compute the square of the distance from the y axis.
  double distance = std::pow(point.x(), 2) + std::pow(point.z(), 2);

  if (distance < 1 && point.y() >= maximum_ - EPSILON) {
    return utility::Vector(0, 1, 0);
  } else if (distance < 1 && point.y() <= minimum_ + EPSILON) {
    return utility::Vector(0, -1, 0);
  } else {
    return utility::Vector(point.x(), 0, point.z());
  }
}

bool Cylinder::CheckCap(const utility::Ray ray, double t) {
  // A helper function to reduce duplication.
  // Checks to see if the intersection at 't' is within a radius of 1 (the
  // radius of the cylinders) from the y axis.

  double x = ray.origin_.x() + t * ray.direction_.x();
  double z = ray.origin_.z() + t * ray.direction_.z();
  return (x * x + z * z) <= 1;
}

void Cylinder::IntersectCaps(const utility::Ray ray,
                             std::vector<Intersection> &xs) {
  // Caps only matter if the cylinder is closed.
  if (!closed_) {
    return;
  }

  // Check for an intersection with the lower end cap by intersecting the ray
  // with the plane at y=cylinder.minimum
  double t = (minimum_ - ray.origin_.y()) / ray.direction_.y();
  if (CheckCap(ray, t)) {
    xs.emplace_back(Intersection(t, std::make_shared<Cylinder>(*this)));
  }

  // Check for an intersection with the upper end cap by intersecting the ray
  // with the plane at y=cylinder.maximum
  t = (maximum_ - ray.origin_.y()) / ray.direction_.y();
  if (CheckCap(ray, t)) {
    xs.emplace_back(Intersection(t, std::make_shared<Cylinder>(*this)));
  }
}

} // namespace geometry
} // namespace raytracer