#include "Sphere.h"

#include <cmath>

namespace raytracer {
namespace geometry {

std::atomic<uint64_t> Sphere::ID = 0;

double Sphere::Discriminant(utility::Ray ray) {
  utility::Vector sphere_to_ray = ray.origin_ - origin_;

  double a = ray.direction_.Dot(ray.direction_);
  double b = 2.0 * ray.direction_.Dot(sphere_to_ray);
  double c = sphere_to_ray.Dot(sphere_to_ray) - 1.0;

  return b * b - 4 * a * c;
}

void Sphere::SetTransform(utility::Matrix transform) { transform_ = transform; }

utility::Vector Sphere::NormalAt(utility::Point world_point) {
  utility::Point object_point = transform_.Inverse() * world_point;
  utility::Vector object_normal = object_point - utility::Point(0, 0, 0);
  utility::Vector world_normal =
      transform_.Inverse().Transpose() * object_normal;
  world_normal[3] = 0;
  return world_normal.Normalize();
}

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Sphere &s1,
                const raytracer::geometry::Sphere &s2) {
  return s1.id_ == s2.id_;
}