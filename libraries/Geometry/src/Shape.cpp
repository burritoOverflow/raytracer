#include "Shape.h"

namespace raytracer {
namespace geometry {

std::atomic<uint64_t> Shape::ID = 0;

void Shape::SetTransform(utility::Matrix transform) { transform_ = transform; }

} // namespace geometry
} // namespace raytracer