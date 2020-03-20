#include "Intersection.h"

#include <algorithm>

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
  sort(intersections_vector.begin(), intersections_vector.end(),
       [](const auto &lhs, const auto &rhs) { return lhs.t_ < rhs.t_; });
  return intersections_vector;
}

std::optional<Intersection> Hit(std::vector<Intersection> &intersections) {
  for (Intersection &i : intersections) {
    if (i.t_ > 0) {
      return i;
    }
  }
  return std::nullopt;
}

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Intersection &i1,
                const raytracer::geometry::Intersection &i2) {
  return i1.t_ == i2.t_ && i1.object_.id_ == i2.object_.id_;
}

bool operator!=(const raytracer::geometry::Intersection &i1,
                const raytracer::geometry::Intersection &i2) {
  return !(i1 == i2);
}