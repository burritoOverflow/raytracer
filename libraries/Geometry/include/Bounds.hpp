#pragma once

#include "Matrix.hpp"
#include "Point.hpp"

namespace raytracer {
namespace geometry {

class Bounds {
public:
  Bounds(utility::Point minimum, utility::Point maximum)
      : minimum_(minimum), maximum_(maximum) {}

  void Merge(const Bounds &other);
  void ExtendToFit(const utility::Point &point);
  Bounds Transform(utility::Matrix &transform);

  utility::Point minimum_;
  utility::Point maximum_;
};

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Bounds &b1,
                const raytracer::geometry::Bounds &b2);