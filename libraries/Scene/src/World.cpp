#include "World.h"

namespace raytracer {
namespace scene {

const bool World::Contains(const PointLight light) const {
  for (const auto &i : light_sources_) {
    if (*i == light) {
      return true;
    }
  }
  return false;
}

const bool World::Contains(const geometry::Sphere object) const {
  for (const auto &i : objects_) {
    if (*i == object) {
      return true;
    }
  }
  return false;
}

std::vector<geometry::Intersection> World::Intersect(utility::Ray ray) {
  std::vector<geometry::Intersection> intersections_vector;
  for (auto &i : objects_) {
    std::vector<geometry::Intersection> xs = geometry::Intersect(*i, ray);
    intersections_vector.insert(std::end(intersections_vector), std::begin(xs),
                                std::end(xs));
  }
  sort(intersections_vector.begin(), intersections_vector.end(),
       [](const auto &lhs, const auto &rhs) { return lhs.t_ < rhs.t_; });
  return intersections_vector;
}

utility::Color World::ShadeHit(geometry::Computations comps) {
  utility::Color color(0, 0, 0);
  for (auto &i : light_sources_) {
    color += Lighting(comps.object.material_, *(light_sources_.front()),
                      comps.point, comps.eye_vector, comps.normal_vector);
  }
  return color;
}

utility::Color World::ColorAt(utility::Ray ray) {
  std::vector<geometry::Intersection> intersections = Intersect(ray);
  auto hit = geometry::Hit(intersections);

  if (hit == std::nullopt) {
    return utility::Color(0, 0, 0);
  }

  geometry::Computations comps = hit->PrepareComputations(ray);
  return ShadeHit(comps);
}

World DefaultWorld() {
  PointLight light(utility::Point(-10, 10, -10), utility::Color(1, 1, 1));
  std::vector<std::shared_ptr<PointLight>> lights = {
      std::make_shared<PointLight>(light)};

  geometry::Sphere s1;
  s1.material_ =
      material::Material(utility::Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200);
  geometry::Sphere s2;
  s2.transform_ = utility::Scaling(0.5, 0.5, 0.5);
  std::vector<std::shared_ptr<geometry::Sphere>> objects = {
      std::make_shared<geometry::Sphere>(s1),
      std::make_shared<geometry::Sphere>(s2)};

  return World(lights, objects);
}

} // namespace scene
} // namespace raytracer