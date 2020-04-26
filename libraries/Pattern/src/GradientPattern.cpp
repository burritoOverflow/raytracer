#include "GradientPattern.h"

namespace raytracer {
namespace pattern {

utility::Color GradientPattern::PatternAt(const utility::Point &point) {
  utility::Vector distance = b_ - a_;
  double fraction = point.x() - floor(point.x());
  return a_ + distance * fraction;
}

} // namespace pattern
} // namespace raytracer