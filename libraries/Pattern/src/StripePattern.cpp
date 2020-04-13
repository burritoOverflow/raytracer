#include "StripePattern.h"

#include <cmath>

#include "AlmostEquals.h"

namespace raytracer {
namespace pattern {

utility::Color StripePattern::StripeAt(utility::Point point) {
  if (AlmostEquals(fmod(floor(point.x()), 2), 0)) {
    return a_;
  }
  return b_;
}

} // namespace pattern
} // namespace raytracer