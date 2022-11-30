#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../3rdparty/stb/stb_image_write.h"

#include "Camera.hpp"
#include "Canvas.hpp"
#include "CreateWorld.hpp"

void write_canvas_to_image(std::filesystem::path &file_path,
                           const raytracer::Canvas &canvas) {
  size_t channels = 3;

  auto get_image_data = [](size_t width, size_t height, size_t channels,
                           const raytracer::Canvas &canvas) {
    std::vector<uint8_t> image_data(canvas.width_ * canvas.height_ * channels);
    size_t i = 0;
    for (size_t col = 0; col < canvas.height_; ++col) {
      for (size_t row = 0; row < canvas.width_; ++row) {
        for (size_t k = 0; k < channels; ++k) {
          image_data[i++] = (uint8_t)std::clamp(
              static_cast<int>(canvas.framebuffer_[row][col][k] * 256), 0, 255);
        }
      }
    }

    return image_data;
  };

  if (file_path.extension() == ".ppm") {
    // Handle special case ppm implemented in the Canvas class
    std::ofstream out(file_path.string().c_str());
    out << canvas.ToPpm();
    out.close();
  } else if (file_path.extension() == ".bmp") {
    stbi_write_bmp(
        file_path.string().c_str(), canvas.width_, canvas.height_, channels,
        get_image_data(canvas.width_, canvas.height_, channels, canvas).data());
  } else if (file_path.extension() == ".jpg") {
    stbi_write_jpg(
        file_path.string().c_str(), canvas.width_, canvas.height_, channels,
        get_image_data(canvas.width_, canvas.height_, channels, canvas).data(),
        100);
  } else if (file_path.extension() == ".png") {
    stbi_write_png(
        file_path.string().c_str(), canvas.width_, canvas.height_, channels,
        get_image_data(canvas.width_, canvas.height_, channels, canvas).data(),
        canvas.width_ * channels);
  } else {
    throw std::invalid_argument("Invalid image file format provided.");
  }
}

int main(void) {
  auto world = CreateWorld();

  // Configure the camera
  raytracer::scene::Camera camera(200, 100, M_PI / 3);
  camera.transform_ = raytracer::utility::ViewTransform(
      raytracer::utility::Point(0, 1.5, -5), raytracer::utility::Point(0, 1, 0),
      raytracer::utility::Vector(0, 1, 0));

  // Render the result to a canvas
  raytracer::Canvas canvas = camera.Render(world);

  // Write the canvas to a file
  write_canvas_to_image(std::filesystem::current_path() / "scene.bmp", canvas);
  std::cout << "\nRender saved to "
            << std::filesystem::current_path() / "scene.bmp" << std::endl;
}
