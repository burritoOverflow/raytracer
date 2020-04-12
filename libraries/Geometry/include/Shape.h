#pragma once

#include "Material.h"
#include "Matrix.h"
#include "Point.h"
#include "Ray.h"

namespace raytracer {
namespace geometry {

class Shape {
public:
  Shape()
      : id_(ID++), transform_(utility::Identity()),
        material_(material::Material()) {}

  void SetTransform(utility::Matrix transform);

  static std::atomic<uint64_t> ID;

  uint64_t id_;
  utility::Matrix transform_;
  material::Material material_;
};

class TestShape : public Shape {
public:
  TestShape() : Shape() {}
};

} // namespace geometry
} // namespace raytracer