#include "Camera.hpp"

#include <execution>
#include <numeric>

#include "ProgressBar.hpp"

namespace raytracer {
namespace scene {

utility::Ray Camera::RayForPixel(size_t px, size_t py) {
  // The offset from the edge of the canvas to the pixel's center
  double x_offset = (px + 0.5) * pixel_size_;
  double y_offset = (py + 0.5) * pixel_size_;

  // The untransformed coordinates of the pixel in world space. (Remember the
  // that camera looks toward -z, so +x is to the *left*.)
  double world_x = half_width_ - x_offset;
  double world_y = half_height_ - y_offset;

  // Using the camera matrix, transform the canvas point and the origin, and
  // then compute the ray's direction vector. (Remember that the canvas is at
  // z=-1.)
  utility::Point pixel =
      transform_.Inverse() * utility::Point(world_x, world_y, -1);
  utility::Point origin = transform_.Inverse() * utility::Point(0, 0, 0);
  utility::Vector direction = (pixel - origin).Normalize();

  return utility::Ray(origin, direction);
}

Canvas Camera::Render(scene::World world) {
  raytracer::Canvas image(hsize_, vsize_);

  size_t num_pixels = hsize_ * vsize_;
  std::vector<size_t> pixels(num_pixels);
  ProgressBar progress_bar(num_pixels);

  std::iota(std::begin(pixels), std::end(pixels), 0);
  std::for_each(std::execution::par, pixels.begin(), pixels.end(),
                [this, &world, &image, &progress_bar](auto &&item) {
                  size_t x = item % hsize_;
                  size_t y = item / hsize_;
                  utility::Ray ray = RayForPixel(x, y);
                  utility::Color color = world.ColorAt(ray);
                  image.WritePixel(x, y, color);

                  progress_bar.Update(item);
                  progress_bar.Print();
                });

  return image;
}

} // namespace scene
} // namespace raytracer