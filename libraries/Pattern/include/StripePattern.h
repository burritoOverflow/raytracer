#pragma once

#include "Color.h"
#include "Matrix.h"
#include "Pattern.h"
#include "Point.h"

namespace raytracer {
namespace pattern {

class StripePattern : public Pattern {
public:
  StripePattern(utility::Color a, utility::Color b) : Pattern(), a_(a), b_(b) {}

  utility::Color PatternAt(const utility::Point &point);

  utility::Color a_;
  utility::Color b_;
};

} // namespace pattern
} // namespace raytracer