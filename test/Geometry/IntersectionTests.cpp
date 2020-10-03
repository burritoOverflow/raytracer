#include "Intersection.h"

#include <gtest/gtest.h>

#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"

using namespace raytracer;

TEST(IntersectionTest, IntersectionEncapsulatesTAndObject) {
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i(3.5, shape);
  ASSERT_DOUBLE_EQ(3.5, i.t_);
  EXPECT_TRUE(shape == i.object_);
}

TEST(IntersectionTest, AggregatingIntersections) {
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i1(1, shape);
  geometry::Intersection i2(2, shape);
  std::vector<geometry::Intersection> xs = geometry::Intersections({i1, i2});
  ASSERT_EQ(2, xs.size());
  ASSERT_DOUBLE_EQ(1, xs[0].t_);
  ASSERT_DOUBLE_EQ(2, xs[1].t_);
}

TEST(IntersectionTest, IntersectSetsTheObjectOnTheIntersection) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Shape> shape = std::make_shared<geometry::Sphere>();
  std::vector<geometry::Intersection> xs = shape->Intersect(r);
  ASSERT_EQ(2, xs.size());
  EXPECT_TRUE(*shape == *xs[0].object_);
  EXPECT_TRUE(*shape == *xs[1].object_);
}

TEST(IntersectionTest, TheHitWhenAllIntersectionsHavePositiveT) {
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i1(1, shape);
  geometry::Intersection i2(2, shape);
  std::vector<geometry::Intersection> xs = geometry::Intersections({i1, i2});
  auto i = geometry::Hit(xs);
  EXPECT_TRUE(i1 == i.value());
}

TEST(IntersectionTest, TheHitWhenSomeIntersectionsHaveNegativeT) {
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i1(-1, shape);
  geometry::Intersection i2(1, shape);
  std::vector<geometry::Intersection> xs = geometry::Intersections({i1, i2});
  auto i = geometry::Hit(xs);
  EXPECT_TRUE(i2 == i.value());
}

TEST(IntersectionTest, TheHitWhenAllIntersectionsHaveNegativeT) {
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i1(-2, shape);
  geometry::Intersection i2(-1, shape);
  std::vector<geometry::Intersection> xs = geometry::Intersections({i1, i2});
  auto i = geometry::Hit(xs);
  EXPECT_TRUE(std::nullopt == i);
}

TEST(IntersectionTest, TheHitIsAlwaysTheLowestNonnegativeIntersection) {
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i1(5, shape);
  geometry::Intersection i2(7, shape);
  geometry::Intersection i3(-3, shape);
  geometry::Intersection i4(2, shape);
  std::vector<geometry::Intersection> xs =
      geometry::Intersections({i1, i2, i3, i4});
  auto i = geometry::Hit(xs);
  EXPECT_TRUE(i4 == i.value());
}

TEST(IntersectionTest, PrecomputeStateOfIntersection) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i(4, shape);
  geometry::Computations comps = i.PrepareComputations(r);
  EXPECT_TRUE(i.t_ == comps.t);
  EXPECT_TRUE(i.object_ == comps.object);
  EXPECT_TRUE(utility::Point(0, 0, -1) == comps.point);
  EXPECT_TRUE(utility::Vector(0, 0, -1) == comps.eye_vector);
  EXPECT_TRUE(utility::Vector(0, 0, -1) == comps.normal_vector);
}

TEST(IntersectionTest, HitWhenIntersectionOccursOnTheOutside) {
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i(4, shape);
  geometry::Computations comps = i.PrepareComputations(r);
  EXPECT_FALSE(comps.inside);
}

TEST(IntersectionTest, HitWhenIntersectionOccursOnTheInside) {
  utility::Ray r(utility::Point(0, 0, 0), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  geometry::Intersection i(1, shape);
  geometry::Computations comps = i.PrepareComputations(r);
  EXPECT_TRUE(utility::Point(0, 0, 1) == comps.point);
  EXPECT_TRUE(utility::Vector(0, 0, -1) == comps.eye_vector);
  EXPECT_TRUE(comps.inside);

  // The normal would have been (0, 0, 1), but it is inverted!
  EXPECT_TRUE(utility::Vector(0, 0, -1) == comps.normal_vector);
}

TEST(IntersectionTest, TheHitShouldOffsetThePoint) {
  utility::Ray ray(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Sphere> shape =
      std::make_shared<geometry::Sphere>();
  shape->transform_ = utility::Translation(0, 0, 1);
  geometry::Intersection intersection(5, shape);
  geometry::Computations comps = intersection.PrepareComputations(ray);
  ASSERT_LT(comps.over_point.z(), -EPSILON / 2);
  ASSERT_GT(comps.point.z(), comps.over_point.z());
}

TEST(IntersectionTest, PrecomputingTheReflectionVector) {
  auto shape = std::make_shared<raytracer::geometry::Plane>();
  utility::Ray ray(utility::Point(0, 1, -1),
                   utility::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  geometry::Intersection intersection(sqrt(2), shape);
  geometry::Computations comps = intersection.PrepareComputations(ray);
  EXPECT_TRUE(utility::Vector(0, sqrt(2) / 2, sqrt(2) / 2) ==
              comps.reflect_vector);
}

TEST(IntersectionTest, FindingN1AndN2AtVariousIntersections) {
  auto A = std::make_shared<raytracer::geometry::Sphere>(
      raytracer::geometry::GlassSphere());
  A->transform_ = utility::Scaling(2, 2, 2);
  A->material_.refractive_index_ = 1.5;

  auto B = std::make_shared<raytracer::geometry::Sphere>(
      raytracer::geometry::GlassSphere());
  B->transform_ = utility::Translation(0, 0, -0.25);
  B->material_.refractive_index_ = 2.0;

  auto C = std::make_shared<raytracer::geometry::Sphere>(
      raytracer::geometry::GlassSphere());
  C->transform_ = utility::Translation(0, 0, 0.25);
  C->material_.refractive_index_ = 2.5;

  utility::Ray ray =
      utility::Ray(utility::Point(0, 0, -4), utility::Vector(0, 0, 1));

  std::vector<geometry::Intersection> xs = geometry::Intersections(
      {geometry::Intersection(2, A), geometry::Intersection(2.75, B),
       geometry::Intersection(3.25, C), geometry::Intersection(4.75, B),
       geometry::Intersection(5.25, C), geometry::Intersection(6, A)});

  geometry::Computations comps0 = xs[0].PrepareComputations(ray, xs);
  ASSERT_DOUBLE_EQ(1.0, comps0.n1);
  ASSERT_DOUBLE_EQ(1.5, comps0.n2);

  geometry::Computations comps1 = xs[1].PrepareComputations(ray, xs);
  ASSERT_DOUBLE_EQ(1.5, comps1.n1);
  ASSERT_DOUBLE_EQ(2.0, comps1.n2);

  geometry::Computations comps2 = xs[2].PrepareComputations(ray, xs);
  ASSERT_DOUBLE_EQ(2.0, comps2.n1);
  ASSERT_DOUBLE_EQ(2.5, comps2.n2);

  geometry::Computations comps3 = xs[3].PrepareComputations(ray, xs);
  ASSERT_DOUBLE_EQ(2.5, comps3.n1);
  ASSERT_DOUBLE_EQ(2.5, comps3.n2);

  geometry::Computations comps4 = xs[4].PrepareComputations(ray, xs);
  ASSERT_DOUBLE_EQ(2.5, comps4.n1);
  ASSERT_DOUBLE_EQ(1.5, comps4.n2);

  geometry::Computations comps5 = xs[5].PrepareComputations(ray, xs);
  ASSERT_DOUBLE_EQ(1.5, comps5.n1);
  ASSERT_DOUBLE_EQ(1.0, comps5.n2);
}