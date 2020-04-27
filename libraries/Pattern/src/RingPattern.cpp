#include "RingPattern.h"

namespace raytracer {
namespace pattern {

utility::Color RingPattern::PatternAt(const utility::Point &point) {
  double distance = sqrt(std::pow(point.x(), 2) + std::pow(point.z(), 2));
  if (AlmostEquals(fmod(floor(distance), 2.0), 0)) {
    return a_;
  }
  return b_;
}

} // namespace pattern
} // namespace raytracer
