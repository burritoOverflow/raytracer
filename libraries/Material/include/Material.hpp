#pragma once

#include <memory>
#include <optional>

#include "Color.hpp"
#include "Pattern.hpp"

namespace raytracer {
namespace material {

class Material {
public:
  Material()
      : color_(utility::Color(1, 1, 1)), pattern_(std::nullopt), ambient_(0.1),
        diffuse_(0.9), specular_(0.9), shininess_(200.0), reflective_(0.0),
        transparency_(0.0), refractive_index_(1.0) {}
  Material(utility::Color color,
           std::optional<std::shared_ptr<pattern::Pattern>> pattern,
           double ambient = 0.1, double diffuse = 0.9, double specular = 0.9,
           double shininess = 200.0, double reflective = 0.0,
           double transparency = 0.0, double refractive_index = 1.0)
      : color_(color), pattern_(pattern), ambient_(ambient), diffuse_(diffuse),
        specular_(specular), shininess_(shininess), reflective_(reflective),
        transparency_(transparency), refractive_index_(refractive_index) {}

  utility::Color color_;
  std::optional<std::shared_ptr<pattern::Pattern>> pattern_;
  double ambient_;
  double diffuse_;
  double specular_;
  double shininess_;
  double reflective_;
  double transparency_;
  double refractive_index_;
};

} // namespace material
} // namespace raytracer

bool operator==(const raytracer::material::Material &m1,
                const raytracer::material::Material &m2);
bool operator!=(const raytracer::material::Material &m1,
                const raytracer::material::Material &m2);
