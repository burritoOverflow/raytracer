#pragma once

#include "Color.h"
#include "Point.h"

namespace raytracer {
namespace scene {

class PointLight {
public:
  PointLight(utility::Point position, utility::Color intensity)
      : position_(position), intensity_(intensity) {}

  utility::Point position_;
  utility::Color intensity_;
};

} // namespace scene
} // namespace raytracer
