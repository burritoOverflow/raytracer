#pragma once

#include <iostream>

#include "AlmostEquals.hpp"

namespace raytracer {
namespace utility {

class Tuple {
public:
  Tuple() {}
  Tuple(double e0, double e1, double e2, double e3) {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
    e[3] = e3;
  }
  inline double x() const { return e[0]; }
  inline double y() const { return e[1]; }
  inline double z() const { return e[2]; }
  inline double w() const { return e[3]; }

  inline const Tuple &operator+() const { return *this; }
  inline Tuple operator-() const { return Tuple(-e[0], -e[1], -e[2], -e[3]); }
  inline double operator[](size_t i) const { return e[i]; }
  inline double &operator[](size_t i) { return e[i]; }

  Tuple &operator+=(const Tuple &t);
  Tuple &operator-=(const Tuple &t);

  inline bool IsPoint() { return fabs(w() - 1.0) < 0.00001; };
  inline bool IsVector() { return fabs(w()) < 0.00001; }

  inline double Magnitude() {
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2] + e[3] * e[3]);
  };

  inline Tuple Normalize() {
    double magnitude = this->Magnitude();
    return Tuple(e[0] / magnitude, e[1] / magnitude, e[2] / magnitude,
                 e[3] / magnitude);
  }

  inline double Dot(const Tuple &t) {
    return e[0] * t.e[0] + e[1] * t.e[1] + e[2] * t.e[2] + e[3] * t.e[3];
  }

  double e[4];
};

} // namespace utility
} // namespace raytracer

std::istream &operator>>(std::istream &is, raytracer::utility::Tuple &t);
std::ostream &operator<<(std::ostream &os, const raytracer::utility::Tuple &t);

bool operator==(const raytracer::utility::Tuple &t1,
                const raytracer::utility::Tuple &t2);
bool operator!=(const raytracer::utility::Tuple &t1,
                const raytracer::utility::Tuple &t2);
raytracer::utility::Tuple operator+(const raytracer::utility::Tuple &t1,
                                    const raytracer::utility::Tuple &t2);
raytracer::utility::Tuple operator-(const raytracer::utility::Tuple &t1,
                                    const raytracer::utility::Tuple &t2);
raytracer::utility::Tuple operator*(const raytracer::utility::Tuple &t1,
                                    const raytracer::utility::Tuple &t2);
raytracer::utility::Tuple operator*(const raytracer::utility::Tuple &t,
                                    double d);
raytracer::utility::Tuple operator*(double d,
                                    const raytracer::utility::Tuple &t);
raytracer::utility::Tuple operator/(const raytracer::utility::Tuple &t,
                                    double d);
