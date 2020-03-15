#include <fstream>
#include <iostream>

#include "Canvas.h"
#include "Point.h"
#include "Vector.h"

class Environment {
public:
  Environment(raytracer::Vector gravity, raytracer::Vector wind)
      : gravity(gravity), wind(wind) {}

  raytracer::Vector gravity;
  raytracer::Vector wind;
};

class Projectile {
public:
  Projectile(raytracer::Point position, raytracer::Vector velocity)
      : position(position), velocity(velocity) {}

  raytracer::Point position;
  raytracer::Vector velocity;
};

Projectile tick(Environment environment, Projectile projectile) {
  raytracer::Point position = projectile.position + projectile.velocity;
  raytracer::Vector velocity =
      projectile.velocity + environment.gravity + environment.wind;
  return Projectile(position, velocity);
};

int main(void) {
  // Projectile starts one unit above the origin
  raytracer::Point start(0, 1, 0);
  raytracer::Vector velocity = raytracer::Vector(1, 1.8, 0).normalize() * 11.25;
  Projectile projectile(start, velocity);

  // Gravity is -0.1 unit/tick, and wind is -0.01 unit/tick
  raytracer::Vector gravity(0, -0.1, 0);
  raytracer::Vector wind(-0.01, 0, 0);
  Environment environment(gravity, wind);

  raytracer::Canvas canvas(900, 550);

  size_t x = static_cast<int>(projectile.position.x());
  size_t y = canvas.height_ - static_cast<int>(projectile.position.y());
  canvas.WritePixel(x, y, raytracer::Color(0, 1, 1));

  while (projectile.position.y() > 0) {
    projectile = tick(environment, projectile);
    size_t x = static_cast<int>(projectile.position.x());
    size_t y = canvas.height_ - static_cast<int>(projectile.position.y());
    if (x < 0 || x >= canvas.width_ || y < 0 || y >= canvas.height_) {
      continue;
    }
    canvas.WritePixel(x, y, raytracer::Color(0, 1, 1));
  }

  // Write the canvas to a file
  std::ofstream out("scene.ppm");
  out << canvas.ToPpm();
  out.close();
}
