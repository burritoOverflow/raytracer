#include "Ray.hpp"

#include <cassert>

namespace raytracer {
namespace utility {

Ray Transform(Ray &r, Matrix &m) { return m * r; }

} // namespace utility
} // namespace raytracer

raytracer::utility::Ray operator*(const raytracer::utility::Matrix &m,
                                  const raytracer::utility::Ray &r) {
  assert(m.rows_ == 4);

  raytracer::utility::Point origin(0, 0, 0);
  origin = m * r.origin_;

  raytracer::utility::Vector direction(0, 0, 0);
  direction = m * r.direction_;

  return raytracer::utility::Ray(origin, direction);
}