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

std::vector<double> Sphere::Intersect(utility::Ray ray) {
  utility::Vector sphere_to_ray = ray.origin_ - origin_;

  double a = ray.direction_.Dot(ray.direction_);
  double b = 2.0 * ray.direction_.Dot(sphere_to_ray);
  double c = sphere_to_ray.Dot(sphere_to_ray) - 1.0;
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return std::vector<double>{};
  }

  double t1 = (-b - sqrt(discriminant)) / (2 * a);
  double t2 = (-b + sqrt(discriminant)) / (2 * a);
  return std::vector<double>{t1, t2};
}

} // namespace geometry
} // namespace raytracer
