#pragma once

#include <string>
#include <vector>

#include "Color.h"

namespace raytracer {
class Canvas {
public:
  Canvas(size_t width, size_t height) : width_(width), height_(height) {
    framebuffer_.resize(width, std::vector<Color>(height));
    for (size_t x = 0; x < width; ++x) {
      for (size_t y = 0; y < height; ++y) {
        framebuffer_[x][y] = Color(0, 0, 0);
      }
    }
  }
  ~Canvas() {}

  inline Color &operator()(size_t x, size_t y) {
    assert(x >= 0 && x < width_);
    assert(y >= 0 && y < height_);
    return framebuffer_[x][y];
  }

  inline Color GetPixel(size_t x, size_t y) const {
    assert(x >= 0 && x < width_);
    assert(y >= 0 && y < height_);
    return framebuffer_[x][y];
  }

  inline void WritePixel(size_t x, size_t y, Color color) {
    (*this)(x, y) = color;
  }

  std::string ToPpm() const;

  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> framebuffer_;
};
} // namespace raytracer
