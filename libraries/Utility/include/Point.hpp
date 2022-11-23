#pragma once

#include "Tuple.hpp"

namespace raytracer {
namespace utility {

class Point : public Tuple {
public:
  Point() : Tuple() {}
  Point(double e0, double e1, double e2) : Tuple(e0, e1, e2, 1.0) {}
  Point(const Tuple &t) : Tuple(t) {}
};

} // namespace utility
} // namespace raytracer
