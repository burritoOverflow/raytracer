#include "Shape.hpp"

namespace raytracer {
namespace geometry {

std::atomic<uint64_t> Shape::ID = 0;

void Shape::SetTransform(utility::Matrix transform) { transform_ = transform; }

std::vector<Intersection> Shape::Intersect(utility::Ray &ray) {
  utility::Matrix transform = transform_.Inverse();
  utility::Ray local_ray = utility::Transform(ray, transform);

  // Return shape-dependent intersections
  return LocalIntersect(local_ray);
}

utility::Vector Shape::NormalAt(utility::Point world_point) {
  utility::Point local_point = WorldToObject(world_point);
  utility::Vector local_normal = LocalNormalAt(local_point);
  return NormalToWorld(local_normal);
}

utility::Point Shape::WorldToObject(utility::Point point) {
  return transform_.Inverse() *
         (parent_ == nullptr ? point : parent_->WorldToObject(point));
}

utility::Vector Shape::NormalToWorld(utility::Vector normal) {
  normal = transform_.Inverse().Transpose() * normal;
  normal[3] = 0; // Set the w coordinate to zero
  normal = normal.Normalize();

  if (parent_ != nullptr) {
    normal = parent_->NormalToWorld(normal);
  }

  return normal;
}

std::tuple<double, double> CheckAxis(double origin, double direction,
                                     double minimum, double maximum) {
  auto tmin_numerator = minimum - origin;
  auto tmax_numerator = maximum - origin;

  double tmin, tmax;
  if (std::abs(direction) >= 0.00001) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    tmin = tmin_numerator * std::numeric_limits<double>::infinity();
    tmax = tmax_numerator * std::numeric_limits<double>::infinity();
  }

  if (tmin > tmax) {
    return {tmax, tmin};
  }
  return {tmin, tmax};
}

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Shape &s1,
                const raytracer::geometry::Shape &s2) {
  return s1.id_ == s2.id_;
}
