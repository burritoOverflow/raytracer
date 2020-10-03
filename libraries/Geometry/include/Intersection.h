#pragma once

#include <initializer_list>
#include <optional>
#include <vector>

#include "Ray.h"
#include "Shape.h"

const double EPSILON = 0.00001;

namespace raytracer {
namespace geometry {

class Shape;

struct Computations {
  double t;
  std::shared_ptr<Shape> object;
  utility::Point point;
  utility::Point over_point;
  utility::Point under_point;
  utility::Vector eye_vector;
  utility::Vector normal_vector;
  utility::Vector reflect_vector;
  bool inside;
  double n1;
  double n2;
};

class Intersection {
public:
  Intersection(double t, std::shared_ptr<Shape> shape)
      : t_(t), object_(shape) {}

  Computations
  PrepareComputations(utility::Ray ray,
                      const std::vector<Intersection> &intersections =
                          std::vector<Intersection>());

  double t_;
  std::shared_ptr<Shape> object_;
};

std::vector<Intersection>
Intersections(const std::initializer_list<Intersection> &intersections);
std::optional<Intersection> Hit(const std::vector<Intersection> &intersections);

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Intersection &i1,
                const raytracer::geometry::Intersection &i2);
bool operator!=(const raytracer::geometry::Intersection &i1,
                const raytracer::geometry::Intersection &i2);
