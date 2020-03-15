#pragma once

#include <cmath>

auto AlmostEquals = [](float a, float b,
                       float epsilon = std::numeric_limits<float>::epsilon()) {
  return (std::fabs(a - b) <= epsilon);
};