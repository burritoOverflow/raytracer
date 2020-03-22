#include <fstream>

#include "Canvas.h"
#include "Color.h"
#include "Intersection.h"
#include "Point.h"
#include "Ray.h"
#include "Sphere.h"

/* Plots position of the hours on the analog clock face */
int main(void) {
  // Start the ray at z = -5
  raytracer::utility::Point ray_origin(0, 0, -5);

  // Put the wall at z = 10
  double wall_z = 10;

  double wall_size = 7.0;
  double canvas_pixels = 500;
  double pixel_size = wall_size / canvas_pixels;
  double half = wall_size / 2;

  raytracer::Canvas canvas(canvas_pixels, canvas_pixels);
  raytracer::utility::Color color(1, 0, 0);
  raytracer::geometry::Sphere shape;

  double world_x, world_y;
  for (size_t y = 0; y < canvas_pixels; ++y) {
    world_y = half - pixel_size * y;
    for (size_t x = 0; x < canvas_pixels; ++x) {
      world_x = -half + pixel_size * x;

      // Describe the point on the wall that the ray will target
      raytracer::utility::Point position(world_x, world_y, wall_z);

      raytracer::utility::Ray r(ray_origin,
                                (position - ray_origin).Normalize());
      auto xs = raytracer::geometry::Intersect(shape, r);

      if (raytracer::geometry::Hit(xs) != std::nullopt) {
        canvas.WritePixel(x, y, color);
      }
    }
  }

  // Write the canvas to a file
  std::ofstream out("scene.ppm");
  out << canvas.ToPpm();
  out.close();
}
