#pragma once

#include "Color.hpp"
#include "Pattern.hpp"
#include "Point.hpp"

namespace raytracer {
namespace pattern {

class GradientPattern : public Pattern {
public:
  GradientPattern(utility::Color a, utility::Color b)
      : Pattern(), a_(a), b_(b) {}

  utility::Color PatternAt(const utility::Point &point);

  utility::Color a_;
  utility::Color b_;
};

} // namespace pattern
} // namespace raytracer