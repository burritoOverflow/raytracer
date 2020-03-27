#pragma once

#include <vector>

#include "Intersection.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"

namespace raytracer {
namespace scene {

class World {
public:
  World() {}
  World(std::vector<PointLight> light_sources,
        std::vector<geometry::Sphere> objects)
      : light_sources_(light_sources), objects_(objects) {}

  const bool Contains(const PointLight light) const;
  const bool Contains(const geometry::Sphere object) const;

  std::vector<geometry::Intersection> Intersect(utility::Ray ray);

  std::vector<PointLight> light_sources_;
  std::vector<geometry::Sphere> objects_;
};

World DefaultWorld();

} // namespace scene
} // namespace raytracer
