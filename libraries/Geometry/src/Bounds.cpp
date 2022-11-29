#include "Bounds.hpp"

namespace raytracer {
namespace geometry {

void Bounds::Merge(const Bounds &other) {
  minimum_ = utility::Point(std::min(minimum_.x(), other.minimum_.x()),
                            std::min(minimum_.y(), other.minimum_.y()),
                            std::min(minimum_.z(), other.minimum_.z()));
  maximum_ = utility::Point(std::max(maximum_.x(), other.maximum_.x()),
                            std::max(maximum_.y(), other.maximum_.y()),
                            std::max(maximum_.z(), other.maximum_.z()));
}

void Bounds::ExtendToFit(const utility::Point &point) {
  minimum_ = utility::Point(std::min(minimum_.x(), point.x()),
                            std::min(minimum_.y(), point.y()),
                            std::min(minimum_.z(), point.z()));
  maximum_ = utility::Point(std::max(maximum_.x(), point.x()),
                            std::max(maximum_.y(), point.y()),
                            std::max(maximum_.z(), point.z()));
}

Bounds Bounds::Transform(utility::Matrix &transform) {
  auto minimum = minimum_;
  auto maximum = maximum_;

  ExtendToFit(transform * minimum);
  ExtendToFit(transform *
              utility::Point(minimum.x(), minimum.y(), maximum.z()));
  ExtendToFit(transform *
              utility::Point(maximum.x(), minimum.y(), minimum.z()));
  ExtendToFit(transform *
              utility::Point(maximum.x(), minimum.y(), maximum.z()));
  ExtendToFit(transform *
              utility::Point(minimum.x(), maximum.y(), minimum.z()));
  ExtendToFit(transform *
              utility::Point(minimum.x(), maximum.y(), minimum.z()));
  ExtendToFit(transform *
              utility::Point(minimum.x(), minimum.y(), maximum.z()));
  ExtendToFit(transform * maximum);

  return *this;
}

} // namespace geometry
} // namespace raytracer

bool operator==(const raytracer::geometry::Bounds &b1,
                const raytracer::geometry::Bounds &b2) {
  return b1.minimum_ == b2.minimum_ && b1.maximum_ == b2.maximum_;
}