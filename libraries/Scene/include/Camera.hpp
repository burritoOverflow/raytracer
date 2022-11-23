#pragma once

#include <iostream>

#include "Canvas.hpp"
#include "Matrix.hpp"
#include "Ray.hpp"
#include "World.hpp"

namespace raytracer {
namespace scene {

class Camera {
public:
  Camera(size_t hsize, size_t vsize, double field_of_view)
      : hsize_(hsize), vsize_(vsize), field_of_view_(field_of_view),
        transform_(utility::Identity()) {
    // Compute the pixel size
    double half_view = tan(field_of_view_ / 2);
    double aspect = hsize_ / (double)vsize_;
    if (aspect >= 1) {
      half_width_ = half_view;
      half_height_ = half_view / aspect;
    } else {
      half_width_ = half_view * aspect;
      half_height_ = half_view;
    }
    pixel_size_ = (half_width_ * 2) / hsize_;
  }

  utility::Ray RayForPixel(size_t px, size_t py);
  Canvas Render(scene::World world);

  size_t hsize_;
  size_t vsize_;
  double field_of_view_;
  utility::Matrix transform_;
  double half_width_;
  double half_height_;
  double pixel_size_;
};

} // namespace scene
} // namespace raytracer
