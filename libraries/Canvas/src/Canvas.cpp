#include "Canvas.h"

#include <sstream>

using namespace raytracer;

std::string Canvas::ToPpm() const {
  const size_t max_line_length = 70;

  std::ostringstream ppm_data;

  // PPM header
  ppm_data << "P3" << std::endl;
  ppm_data << width_ << " " << height_ << std::endl;
  ppm_data << "255" << std::endl;

  // PPM data
  size_t char_count = 0;
  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      Color color = GetPixel(x, y);

      for (size_t k = 0; k < 3; ++k) {
        ppm_data << std::clamp(static_cast<int>(color[k] * 256), 0, 255);
        char_count += 3;

        if (x == width_ - 1 && k == 2) {
          // Do nothing
        } else {
          if (char_count < max_line_length - 4) {
            ppm_data << " ";
            char_count++;
          } else {
            ppm_data << std::endl;
            char_count = 0;
          }
        }
      }
    }
    ppm_data << std::endl;
    char_count = 0;
  }
  return ppm_data.str();
}