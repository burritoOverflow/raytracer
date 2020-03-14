#include <iostream>

#include "Point.h"
#include "Tuple.h"
#include "Vector.h"

int main(void) {
  raytracer::Vector v1(1, 2, 3);
  raytracer::Vector v2(2, 3, 4);
  std::cout << v1.cross(v2) << std::endl;
}
