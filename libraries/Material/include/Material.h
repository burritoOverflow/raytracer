#pragma once

#include "Color.h"

namespace raytracer {
namespace material {

class Material {
public:
  Material()
      : color_(utility::Color(1, 1, 1)), ambient_(0.1), diffuse_(0.9),
        specular_(0.9), shininess_(200.0) {}
  Material(utility::Color color, double ambient = 0.1, double diffuse = 0.9,
           double specular = 0.9, double shininess = 200.0)
      : color_(color), ambient_(ambient), diffuse_(diffuse),
        specular_(specular), shininess_(shininess) {}

  utility::Color color_;
  double ambient_;
  double diffuse_;
  double specular_;
  double shininess_;
};

} // namespace material
} // namespace raytracer

bool operator==(const raytracer::material::Material &m1,
                const raytracer::material::Material &m2);
bool operator!=(const raytracer::material::Material &m1,
                const raytracer::material::Material &m2);