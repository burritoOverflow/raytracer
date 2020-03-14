#include <iostream>

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
  // Velocity is normalized 1 unit/tick
  raytracer::Point initial_position(0, 1, 0);
  raytracer::Vector initial_velocity(1, 1, 0);
  Projectile projectile(initial_position, initial_velocity.normalize());

  // Gravity is -0.1 unit/tick, and wind is -0.01 unit/tick
  raytracer::Vector gravity(0, -0.1, 0);
  raytracer::Vector wind(-0.01, 0, 0);
  Environment environment(gravity, wind);

  size_t num_ticks = 0;
  while (projectile.position.y() > 0) {
    std::cout << "Position: " << projectile.position << std::endl;
    projectile = tick(environment, projectile);
    ++num_ticks;
  }
  std::cout << "Total ticks: " << num_ticks << std::endl;
}
