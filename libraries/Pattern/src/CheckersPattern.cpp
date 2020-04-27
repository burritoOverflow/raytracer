#include "CheckersPattern.h"

namespace raytracer {
namespace pattern {

utility::Color CheckersPattern::PatternAt(const utility::Point &point) {
  double sum = floor(point.x()) + floor(point.y()) + floor(point.z());
  if (AlmostEquals(fmod(sum, 2), 0)) {
    return a_;
  }
  return b_;
}

} // namespace pattern
} // namespace raytracer