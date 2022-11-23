#include "Material.hpp"

bool operator==(const raytracer::material::Material &m1,
                const raytracer::material::Material &m2) {
  return m1.color_ == m2.color_ && m1.ambient_ == m2.ambient_ &&
         m1.diffuse_ == m2.diffuse_ && m1.specular_ == m2.specular_ &&
         m1.shininess_ == m2.shininess_;
}

bool operator!=(const raytracer::material::Material &m1,
                const raytracer::material::Material &m2) {
  return !(m1 == m2);
}