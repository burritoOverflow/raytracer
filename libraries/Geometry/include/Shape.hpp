#pragma once

#include <atomic>

#include "Intersection.hpp"
#include "Material.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include "Ray.hpp"

namespace raytracer {
namespace geometry {

class Intersection;

class Shape {
public:
  Shape()
      : id_(ID++), transform_(utility::Identity()),
        material_(material::Material()) {}

  void SetTransform(utility::Matrix transform);
  std::vector<Intersection> Intersect(utility::Ray &ray);
  utility::Vector NormalAt(utility::Point point);

  static std::atomic<uint64_t> ID;

  uint64_t id_;
  utility::Matrix transform_;
  material::Material material_;

protected:
  virtual std::vector<Intersection> LocalIntersect(utility::Ray &ray) = 0;
  virtual utility::Vector LocalNormalAt(utility::Point &point) = 0;
};

// TODO: Move to test/ directory
class TestShape : public Shape {
public:
  TestShape()
      : Shape(), saved_ray_(utility::Ray(utility::Point(), utility::Vector())) {
  }

  std::vector<Intersection> LocalIntersect(utility::Ray &ray) {
    saved_ray_ = ray;
    return {};
  };

  utility::Vector LocalNormalAt(utility::Point &point) {
    return utility::Vector(point.x(), point.y(), point.z());
  }

  utility::Ray saved_ray_;
};

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Shape &s1,
                const raytracer::geometry::Shape &s2);
