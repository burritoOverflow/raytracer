#pragma once

#include "Color.hpp"
#include "Matrix.hpp"

namespace raytracer {
namespace pattern {

class Pattern {
public:
  Pattern() : transform_(utility::Identity()) {}

  utility::Color PatternAtShape(utility::Matrix object_transform,
                                const utility::Point &world_point) {
    utility::Point object_point = object_transform.Inverse() * world_point;
    utility::Point pattern_point = transform_.Inverse() * object_point;
    return PatternAt(pattern_point);
  }

  utility::Matrix transform_;

protected:
  virtual utility::Color PatternAt(const utility::Point &point) = 0;
};

// TODO: Move to test/ directory
class TestPattern : public Pattern {
public:
  TestPattern() : Pattern() {}

  utility::Color PatternAt(const utility::Point &point) {
    return utility::Color(point.x(), point.y(), point.z());
  }
};

} // namespace pattern
} // namespace raytracer
