#include "Tuple.hpp"

#include <iostream>

using namespace raytracer::utility;

Tuple &Tuple::operator+=(const Tuple &t) {
  e[0] += t.e[0];
  e[1] += t.e[1];
  e[2] += t.e[2];
  e[3] += t.e[3];
  return *this;
}

Tuple &Tuple::operator-=(const Tuple &t) {
  e[0] -= t.e[0];
  e[1] -= t.e[1];
  e[2] -= t.e[2];
  e[3] -= t.e[3];
  return *this;
}

std::istream &operator>>(std::istream &is, Tuple &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2] >> t.e[3];
  return is;
}

std::ostream &operator<<(std::ostream &os, const Tuple &t) {
  os << t.e[0] << " " << t.e[1] << " " << t.e[2] << " " << t.e[3];
  return os;
}

bool operator==(const Tuple &t1, const Tuple &t2) {
  for (size_t i = 0; i < 4; ++i) {
    if (!AlmostEquals(t1[i], t2[i])) {
      return false;
    };
  }
  return true;
}

bool operator!=(const Tuple &t1, const Tuple &t2) { return !(t1 == t2); }

Tuple operator+(const Tuple &t1, const Tuple &t2) {
  return Tuple(t1[0] + t2[0], t1[1] + t2[1], t1[2] + t2[2], t1[3] + t2[3]);
}

Tuple operator-(const Tuple &t1, const Tuple &t2) {
  return Tuple(t1[0] - t2[0], t1[1] - t2[1], t1[2] - t2[2], t1[3] - t2[3]);
}

Tuple operator*(const Tuple &t1, const Tuple &t2) {
  return Tuple(t1.e[0] * t2.e[0], t1.e[1] * t2.e[1], t1.e[2] * t2.e[2],
               t1.e[3] * t2.e[3]);
}

Tuple operator*(const Tuple &t, double d) {
  return Tuple(d * t[0], d * t[1], d * t[2], d * t[3]);
};

Tuple operator*(double d, const Tuple &t) {
  return Tuple(d * t[0], d * t[1], d * t[2], d * t[3]);
}

Tuple operator/(const Tuple &t, double d) {
  return Tuple(t[0] / d, t[1] / d, t[2] / d, t[3] / d);
}