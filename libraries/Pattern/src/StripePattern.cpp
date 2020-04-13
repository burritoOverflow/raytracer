#include "StripePattern.h"

#include <cmath>

#include "AlmostEquals.h"

namespace raytracer {
namespace pattern {

utility::Color StripePattern::StripeAt(const utility::Point &point) {
  if (AlmostEquals(fmod(floor(point.x()), 2), 0)) {
    return a_;
  }
  return b_;
}

utility::Color
StripePattern::StripeAtObject(utility::Matrix object_transform,
                              const utility::Point &world_point) {
  utility::Point object_point = object_transform.Inverse() * world_point;
  utility::Point pattern_point = transform_.Inverse() * object_point;
  return StripeAt(pattern_point);
}

} // namespace pattern
} // namespace raytracer