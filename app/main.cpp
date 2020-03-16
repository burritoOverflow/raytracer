#include <fstream>

#include "Canvas.h"
#include "Matrix.h"
#include "Point.h"

/* Plots position of the hours on the analog clock face */
int main(void) {
  size_t width = 100;
  size_t height = width;
  raytracer::Canvas canvas(width, height);
  double radius = (3. / 8) * width;

  raytracer::Point point(0, 0, 1);
  raytracer::Point canvas_center(width / 2, height / 2, 0);
  raytracer::Point hour_position(0, 0, 0);

  for (size_t i = 0; i < 12; ++i) {
    hour_position = raytracer::RotationY(i * M_PI / 6) * point;
    std::cout << i << ": " << hour_position << std::endl;
    size_t x = canvas_center.x() + static_cast<int>(radius * hour_position.x());
    size_t y = canvas_center.y() - static_cast<int>(radius * hour_position.z());
    std::cout << "x: " << x << " z: " << y << std::endl;
    canvas.WritePixel(x, y, raytracer::Color(1, 1, 1));
  }

  // Write the canvas to a file
  std::ofstream out("scene.ppm");
  out << canvas.ToPpm();
  out.close();
}
