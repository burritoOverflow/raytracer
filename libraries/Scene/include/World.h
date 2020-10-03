#pragma once

#include <vector>

#include "Intersection.h"
#include "Light.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"

namespace raytracer {
namespace scene {

class World {
public:
  World() {}
  World(std::vector<std::shared_ptr<PointLight>> light_sources,
        std::vector<std::shared_ptr<geometry::Shape>> objects)
      : light_sources_(light_sources), objects_(objects) {}

  const bool Contains(const PointLight light) const;
  const bool Contains(const std::shared_ptr<geometry::Shape> object) const;

  std::vector<geometry::Intersection> Intersect(utility::Ray ray);
  utility::Color ShadeHit(geometry::Computations comps, size_t remaining = 5);
  utility::Color ColorAt(utility::Ray ray, size_t remaining = 5);
  bool IsShadowed(utility::Point point);

  utility::Color ReflectedColor(geometry::Computations comps,
                                size_t remaining = 5);
  utility::Color RefractedColor(geometry::Computations comps,
                                size_t remaining = 5);

  std::vector<std::shared_ptr<PointLight>> light_sources_;
  std::vector<std::shared_ptr<geometry::Shape>> objects_;
};

World DefaultWorld();

} // namespace scene
} // namespace raytracer
