#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

auto AlmostEquals = [](float a, float b,
                       float epsilon = std::numeric_limits<float>::epsilon()) {
  return (std::fabs(a - b) <= epsilon);
};

namespace raytracer {
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

  inline double magnitude() {
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2] + e[3] * e[3]);
  };

  inline Tuple normalize() {
    double magnitude = this->magnitude();
    return Tuple(e[0] / magnitude, e[1] / magnitude, e[2] / magnitude,
                 e[3] / magnitude);
  }

  inline double dot(const Tuple &t) {
    return e[0] * t.e[0] + e[1] * t.e[1] + e[2] * t.e[2] + e[3] * t.e[3];
  }

  double e[4];
};
} // namespace raytracer

std::istream &operator>>(std::istream &is, raytracer::Tuple &t);
std::ostream &operator<<(std::ostream &os, const raytracer::Tuple &t);

bool operator==(const raytracer::Tuple &t1, const raytracer::Tuple &t2);
bool operator!=(const raytracer::Tuple &t1, const raytracer::Tuple &t2);
raytracer::Tuple operator+(const raytracer::Tuple &t1,
                           const raytracer::Tuple &t2);
raytracer::Tuple operator-(const raytracer::Tuple &t1,
                           const raytracer::Tuple &t2);
raytracer::Tuple operator*(const raytracer::Tuple &t1,
                           const raytracer::Tuple &t2);
raytracer::Tuple operator*(const raytracer::Tuple &t, double d);
raytracer::Tuple operator*(double d, const raytracer::Tuple &t);
raytracer::Tuple operator/(const raytracer::Tuple &t, double d);
