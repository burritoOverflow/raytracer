#include "Light.h"

namespace raytracer {
namespace scene {

utility::Color Lighting(material::Material material, PointLight light,
                        utility::Point point, utility::Vector eye_vector,
                        utility::Vector normal_vector, bool in_shadow) {
  // Combine the surface color with the light's color/intensity
  utility::Color effective_color = material.color_ * light.intensity_;

  // Find the direction to the light source
  utility::Vector light_vector = (light.position_ - point).Normalize();

  // Compute the ambient contribution
  utility::Color ambient = effective_color * material.ambient_;

  // light_dot_normal represents the cosine of the angle between the light
  // vector and the normal vector. A negative number means the light is on the
  // other side of the surface.
  double light_dot_normal = light_vector.Dot(normal_vector);
  utility::Color diffuse, specular;
  if (light_dot_normal < 0) {
    diffuse = utility::Color(0, 0, 0);
    specular = utility::Color(0, 0, 0);
  } else {
    // Compute the diffuse contribution
    diffuse = effective_color * material.diffuse_ * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the reflection
    // vector and the eye vector. A negative number means the light reflects
    // away from the eye.
    utility::Vector reflect_vector = -light_vector.Reflect(normal_vector);
    double reflect_dot_eye = reflect_vector.Dot(eye_vector);

    if (reflect_dot_eye <= 0) {
      specular = utility::Color(0, 0, 0);
    } else {
      // Compute the specular contribution
      double factor = std::pow(reflect_dot_eye, material.shininess_);
      specular = light.intensity_ * material.specular_ * factor;
    }
  }

  // Ignore the specular and diffuse component if the point is in shadow
  if (in_shadow) {
    return ambient;
  }

  // Add the three contributions together to get the final shading
  return ambient + diffuse + specular;
}

} // namespace scene
} // namespace raytracer

bool operator==(const raytracer::scene::PointLight &l1,
                const raytracer::scene::PointLight &l2) {
  return l1.position_ == l2.position_ && l1.intensity_ == l2.intensity_;
}
