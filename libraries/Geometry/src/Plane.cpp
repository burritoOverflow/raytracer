#include "Plane.hpp"

namespace raytracer {
namespace geometry {

std::vector<Intersection> Plane::LocalIntersect(utility::Ray &ray) {
  if (abs(ray.direction_.y()) < EPSILON) {
    return {};
  }

  double t = -ray.origin_.y() / ray.direction_.y();
  return std::vector<Intersection>{
      Intersection(t, std::make_shared<Plane>(*this))};
}

utility::Vector Plane::LocalNormalAt(utility::Point &point) {
  return utility::Vector(0, 1, 0);
}

} // namespace geometry
} // namespace raytracer
