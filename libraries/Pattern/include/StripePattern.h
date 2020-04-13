#pragma once

#include "Color.h"
#include "Matrix.h"
#include "Point.h"

namespace raytracer {
namespace pattern {

class StripePattern {
public:
  StripePattern(utility::Color a, utility::Color b)
      : a_(a), b_(b), transform_(utility::Identity()) {}

  utility::Color StripeAt(const utility::Point &point);
  utility::Color StripeAtObject(utility::Matrix object_transform,
                                const utility::Point &world_point);

  utility::Color a_;
  utility::Color b_;
  utility::Matrix transform_;
};

} // namespace pattern
} // namespace raytracer