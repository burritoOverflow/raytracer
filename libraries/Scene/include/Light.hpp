#pragma once

#include "Color.hpp"
#include "Material.hpp"
#include "Point.hpp"
#include "Vector.hpp"

namespace raytracer {
namespace scene {

class PointLight {
public:
  PointLight(utility::Point position, utility::Color intensity)
      : position_(position), intensity_(intensity) {}

  utility::Point position_;
  utility::Color intensity_;
};

utility::Color Lighting(std::shared_ptr<material::Material> material,
                        utility::Matrix object_transform, PointLight light,
                        utility::Point point, utility::Vector eye_vector,
                        utility::Vector normal_vector, bool in_shadow);

} // namespace scene
} // namespace raytracer

bool operator==(const raytracer::scene::PointLight &l1,
                const raytracer::scene::PointLight &l2);
