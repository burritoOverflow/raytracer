#pragma once

#include "Tuple.hpp"

namespace raytracer {
namespace utility {

class Color : public Tuple {
public:
  Color() : Tuple() {}
  Color(double e0, double e1, double e2) : Tuple(e0, e1, e2, 0) {}
  Color(const Tuple &t) : Tuple(t) {}

  inline double red() const { return e[0]; }
  inline double green() const { return e[1]; }
  inline double blue() const { return e[2]; }
};

} // namespace utility
} // namespace raytracer
