#include "Sphere.h"

#include <cmath>

namespace raytracer {
namespace geometry {

double Sphere::Discriminant(utility::Ray ray) {
  utility::Vector sphere_to_ray = ray.origin_ - origin_;

  double a = ray.direction_.Dot(ray.direction_);
  double b = 2.0 * ray.direction_.Dot(sphere_to_ray);
  double c = sphere_to_ray.Dot(sphere_to_ray) - 1.0;

  return b * b - 4 * a * c;
}

std::vector<Intersection> Sphere::Intersect(utility::Ray &ray) {
  utility::Matrix transform = transform_.Inverse();
  utility::Ray ray_transformed = utility::Transform(ray, transform);

  utility::Vector sphere_to_ray = ray_transformed.origin_ - origin_;

  double a = ray_transformed.direction_.Dot(ray_transformed.direction_);
  double b = 2.0 * ray_transformed.direction_.Dot(sphere_to_ray);
  double c = sphere_to_ray.Dot(sphere_to_ray) - 1.0;
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return std::vector<Intersection>{};
  }

  double t1 = (-b - sqrt(discriminant)) / (2 * a);
  double t2 = (-b + sqrt(discriminant)) / (2 * a);
  return std::vector<Intersection>{
      Intersection(t1, std::make_shared<Sphere>(*this)),
      Intersection(t2, std::make_shared<Sphere>(*this))};
}

utility::Vector Sphere::NormalAt(utility::Point world_point) {
  utility::Point object_point = transform_.Inverse() * world_point;
  utility::Vector object_normal = object_point - utility::Point(0, 0, 0);
  utility::Vector world_normal =
      transform_.Inverse().Transpose() * object_normal;
  world_normal[3] = 0; // Set the w coordinate to zero
  return world_normal.Normalize();
}

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Sphere &s1,
                const raytracer::geometry::Sphere &s2) {
  return s1.id_ == s2.id_;
}