#include "StripePattern.hpp"

#include <cmath>

#include "AlmostEquals.hpp"

namespace raytracer {
namespace pattern {

utility::Color StripePattern::PatternAt(const utility::Point &point) {
  if (AlmostEquals(fmod(floor(point.x()), 2), 0)) {
    return a_;
  }
  return b_;
}

} // namespace pattern
} // namespace raytracer