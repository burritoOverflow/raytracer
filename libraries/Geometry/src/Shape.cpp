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
  utility::Point local_point = transform_.Inverse() * world_point;
  utility::Vector local_normal = LocalNormalAt(local_point);
  utility::Vector world_normal =
      transform_.Inverse().Transpose() * local_normal;
  world_normal[3] = 0; // Set the w coordinate to zero
  return world_normal.Normalize();
}

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Shape &s1,
                const raytracer::geometry::Shape &s2) {
  return s1.id_ == s2.id_;
}
