#pragma once

#include "Color.h"
#include "Point.h"

namespace raytracer {
namespace pattern {

class StripePattern {
public:
  StripePattern(utility::Color a, utility::Color b) : a_(a), b_(b) {}

  utility::Color StripeAt(utility::Point point);

  utility::Color a_;
  utility::Color b_;
};

} // namespace pattern
} // namespace raytracer