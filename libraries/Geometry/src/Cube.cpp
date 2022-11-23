#include "Cube.hpp"

#include <algorithm>

namespace raytracer {
namespace geometry {

std::vector<Intersection> Cube::LocalIntersect(utility::Ray &ray) {
  auto [xtmin, xtmax] = CheckAxis(ray.origin_.x(), ray.direction_.x());
  auto [ytmin, ytmax] = CheckAxis(ray.origin_.y(), ray.direction_.y());
  auto [ztmin, ztmax] = CheckAxis(ray.origin_.z(), ray.direction_.z());

  auto tmin = std::max({xtmin, ytmin, ztmin});
  auto tmax = std::min({xtmax, ytmax, ztmax});

  if (tmin > tmax || tmax < 0) {
    return {};
  }
  return std::vector<Intersection>{
      Intersection(tmin, std::make_shared<Cube>(*this)),
      Intersection(tmax, std::make_shared<Cube>(*this))};
}

utility::Vector Cube::LocalNormalAt(utility::Point &point) {
  auto maxc =
      std::max({std::abs(point.x()), std::abs(point.y()), std::abs(point.z())});

  if (maxc == std::abs(point.x())) {
    return utility::Vector(point.x(), 0, 0);
  } else if (maxc == std::abs(point.y())) {
    return utility::Vector(0, point.y(), 0);
  }
  return utility::Vector(0, 0, point.z());
}

std::tuple<double, double> Cube::CheckAxis(double origin, double direction) {
  auto tmin_numerator = -1 - origin;
  auto tmax_numerator = 1 - origin;

  double tmin, tmax;
  if (std::abs(direction) >= EPSILON) {
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