#include "Intersection.h"

namespace raytracer {
namespace geometry {

std::vector<Intersection> Intersect(Sphere &sphere, utility::Ray ray) {
  utility::Vector sphere_to_ray = ray.origin_ - sphere.origin_;

  double a = ray.direction_.Dot(ray.direction_);
  double b = 2.0 * ray.direction_.Dot(sphere_to_ray);
  double c = sphere_to_ray.Dot(sphere_to_ray) - 1.0;
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return std::vector<Intersection>{};
  }

  double t1 = (-b - sqrt(discriminant)) / (2 * a);
  double t2 = (-b + sqrt(discriminant)) / (2 * a);
  return std::vector<Intersection>{Intersection(t1, sphere),
                                   Intersection(t2, sphere)};
}

std::vector<Intersection>
Intersections(const std::initializer_list<Intersection> &intersections) {
  std::vector<Intersection> intersections_vector;
  for (auto intersection : intersections) {
    intersections_vector.push_back(intersection);
  }
  return intersections_vector;
}

} // namespace geometry
} // namespace raytracer
