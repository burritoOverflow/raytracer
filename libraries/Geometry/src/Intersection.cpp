#include "Intersection.h"

#include <algorithm>

namespace raytracer {
namespace geometry {

Computations Intersection::PrepareComputations(utility::Ray ray) {
  Computations comps;

  // Copy the intersection's properties, for convenience
  comps.t = t_;
  comps.object = object_;

  // Precompute some useful values
  comps.point = ray.Position(comps.t);
  comps.eye_vector = -ray.direction_;
  comps.normal_vector = comps.object.NormalAt(comps.point);

  if (comps.normal_vector.Dot(comps.eye_vector) < 0) {
    comps.inside = true;
    comps.normal_vector = -comps.normal_vector;
  } else {
    comps.inside = false;
  }

  comps.over_point = comps.point + comps.normal_vector * EPSILON;

  return comps;
}

std::vector<Intersection> Intersect(Sphere &sphere, utility::Ray ray) {
  utility::Matrix transform = sphere.transform_.Inverse();
  utility::Ray ray_transformed = utility::Transform(ray, transform);

  utility::Vector sphere_to_ray = ray_transformed.origin_ - sphere.origin_;

  double a = ray_transformed.direction_.Dot(ray_transformed.direction_);
  double b = 2.0 * ray_transformed.direction_.Dot(sphere_to_ray);
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
