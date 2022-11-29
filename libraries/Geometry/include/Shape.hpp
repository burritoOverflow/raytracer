#pragma once

#include <atomic>

#include "Bounds.hpp"
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
        material_(std::make_shared<material::Material>()), parent_(nullptr) {}

  void SetTransform(utility::Matrix transform);
  std::vector<Intersection> Intersect(utility::Ray &ray);
  utility::Vector NormalAt(utility::Point point);
  utility::Point WorldToObject(utility::Point point);
  utility::Vector NormalToWorld(utility::Vector normal);
  virtual Bounds ComputeBounds() = 0;

  static std::atomic<uint64_t> ID;

  uint64_t id_;
  utility::Matrix transform_;
  std::shared_ptr<material::Material> material_;
  Shape *parent_;

protected:
  virtual std::vector<Intersection> LocalIntersect(utility::Ray &ray) = 0;
  virtual utility::Vector LocalNormalAt(utility::Point &point) = 0;
};

// TODO: Move to test/ directory
class TestShape : public Shape {
public:
  std::vector<Intersection> LocalIntersect(utility::Ray &ray) {
    saved_ray_ = ray;
    return {};
  };

  utility::Vector LocalNormalAt(utility::Point &point) {
    return utility::Vector(point.x(), point.y(), point.z());
  }

  Bounds ComputeBounds() {
    return Bounds(utility::Point(0, 0, 0), utility::Point(0, 0, 0));
  }

  utility::Ray saved_ray_ = utility::Ray(utility::Point(), utility::Vector());
};

std::tuple<double, double> CheckAxis(double origin, double direction,
                                     double minimum = -1, double maximum = 1);

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Shape &s1,
                const raytracer::geometry::Shape &s2);
