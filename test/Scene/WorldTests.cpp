#include "World.h"

#include <algorithm>
#include <gtest/gtest.h>

using namespace raytracer;

TEST(WorldTest, CreateWorld) {
  scene::World w;
  ASSERT_EQ(0, w.objects_.size());
  ASSERT_EQ(0, w.light_sources_.size());
}

TEST(WorldTest, DefaultWorld) {
  scene::PointLight light(utility::Point(-10, 10, -10),
                          utility::Color(1, 1, 1));
  std::shared_ptr<geometry::Sphere> s1 = std::make_shared<geometry::Sphere>();
  s1->material_ = material::Material(utility::Color(0.8, 1.0, 0.6),
                                     std::nullopt, 0.1, 0.7, 0.2, 200);
  std::shared_ptr<geometry::Sphere> s2 = std::make_shared<geometry::Sphere>();
  s2->transform_ = utility::Scaling(0.5, 0.5, 0.5);
  scene::World w = scene::DefaultWorld();

  // The initialization of the world will also increment the ids, which are used
  // for comparison. Therefore, we increment the ids by 2.
  s1->id_ += 2;
  s2->id_ += 2;

  EXPECT_TRUE(w.Contains(light));
  EXPECT_TRUE(w.Contains(s1));
  EXPECT_TRUE(w.Contains(s2));
}

TEST(WorldTest, IntersectWorldWithRay) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::vector<geometry::Intersection> xs = w.Intersect(r);
  ASSERT_EQ(4, xs.size());
  EXPECT_TRUE(4 == xs[0].t_);
  EXPECT_TRUE(4.5 == xs[1].t_);
  EXPECT_TRUE(5.5 == xs[2].t_);
  EXPECT_TRUE(6 == xs[3].t_);
}

TEST(WorldTest, ShadeIntersection) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Shape> shape = w.objects_.front();
  geometry::Intersection i(4, shape);
  geometry::Computations comps = i.PrepareComputations(r);
  utility::Color c = w.ShadeHit(comps);
  EXPECT_TRUE(utility::Color(0.38066119308103435, 0.47582649135129296,
                             0.28549589481077575) == c);
}

TEST(WorldTest, ShadeIntersectionFromTheInside) {
  scene::World w = scene::DefaultWorld();
  w.light_sources_[0] = std::make_shared<scene::PointLight>(
      scene::PointLight(utility::Point(0, 0.25, 0), utility::Color(1, 1, 1)));
  utility::Ray r(utility::Point(0, 0, 0), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Shape> shape = w.objects_.at(1);
  geometry::Intersection i(0.5, shape);
  geometry::Computations comps = i.PrepareComputations(r);
  utility::Color c = w.ShadeHit(comps);
  EXPECT_TRUE(utility::Color(0.9049844720832575, 0.9049844720832575,
                             0.9049844720832575) == c);
}

TEST(WorldTest, TheColorWhenRayMisses) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 1, 0));
  utility::Color c = w.ColorAt(r);
  EXPECT_TRUE(utility::Color(0, 0, 0) == c);
}

TEST(WorldTest, TheColorWhenRayHits) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  utility::Color c = w.ColorAt(r);
  EXPECT_TRUE(utility::Color(0.38066119308103435, 0.47582649135129296,
                             0.28549589481077575) == c);
}

TEST(WorldTest, TheColorWithIntersectionBehindTheRay) {
  scene::World w = scene::DefaultWorld();

  auto outer = w.objects_.front();
  outer->material_.ambient_ = 1;

  auto inner = w.objects_.at(1);
  inner->material_.ambient_ = 1;

  utility::Ray r(utility::Point(0, 0, 0.75), utility::Vector(0, 0, -1));
  utility::Color c = w.ColorAt(r);
  EXPECT_TRUE(inner->material_.color_ == c);
}

TEST(WorldTest, ThereIsNoShadowWhenNothingIsCollinearWithPointAndLight) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(0, 10, 0);
  EXPECT_FALSE(w.IsShadowed(p));
}

TEST(WorldTest, TheShadowWhenAnObjectIsBetweenThePointAndTheLight) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(10, -10, 10);
  EXPECT_TRUE(w.IsShadowed(p));
}

TEST(WorldTest, ThereIsNoShadowWhenAnObjectIsBehindTheLight) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(-20, 20, -20);
  EXPECT_FALSE(w.IsShadowed(p));
}

TEST(WorldTest, ThereIsNoShadowWhenAnObjectIsBehindThePoint) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(-2, 2, -2);
  EXPECT_FALSE(w.IsShadowed(p));
}

TEST(WorldTest, TheShadeHitFunctionIsGivenAnIntersectionInShadow) {
  scene::World world;
  world.light_sources_.push_back(std::make_shared<raytracer::scene::PointLight>(
      scene::PointLight(utility::Point(0, 0, -10), utility::Color(1, 1, 1))));

  std::shared_ptr<geometry::Sphere> s1 = std::make_shared<geometry::Sphere>();
  world.objects_.push_back(s1);

  std::shared_ptr<geometry::Sphere> s2 = std::make_shared<geometry::Sphere>();
  s2->transform_ = utility::Translation(0, 0, 10);
  world.objects_.push_back(s2);

  utility::Ray ray(utility::Point(0, 0, 5), utility::Vector(0, 0, 1));
  geometry::Intersection intersection(4, s2);
  geometry::Computations comps = intersection.PrepareComputations(ray);
  utility::Color color = world.ShadeHit(comps);

  EXPECT_TRUE(utility::Color(0.1, 0.1, 0.1) == color);
}

TEST(WorldTest, TheReflectedColorForANonreflectiveMaterial) {
  scene::World world = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  auto shape = world.objects_[1];
  shape->material_.ambient_ = 1;
  geometry::Intersection intersection(1, shape);

  geometry::Computations comps = intersection.PrepareComputations(r);
  utility::Color color = world.ReflectedColor(comps);

  EXPECT_TRUE(utility::Color(0, 0, 0) == color);
}

TEST(WorldTest, TheReflectedColorForAReflectiveMaterial) {
  scene::World world = scene::DefaultWorld();
  std::shared_ptr<geometry::Plane> shape = std::make_shared<geometry::Plane>();
  shape->material_.reflective_ = 0.5;
  shape->transform_ = utility::Translation(0, -1, 0);
  world.objects_.push_back(shape);
  utility::Ray ray = utility::Ray(
      utility::Point(0, 0, -3), utility::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  geometry::Intersection intersection(sqrt(2), shape);

  geometry::Computations comps = intersection.PrepareComputations(ray);
  utility::Color color = world.ReflectedColor(comps);

  EXPECT_TRUE(utility::Color(0.19033232037953, 0.23791540047442,
                             0.14274924028465) == color);
}

TEST(WorldTest, ShadeHitWithAReflectiveMaterial) {
  scene::World world = scene::DefaultWorld();
  std::shared_ptr<geometry::Plane> shape = std::make_shared<geometry::Plane>();
  shape->material_.reflective_ = 0.5;
  shape->transform_ = utility::Translation(0, -1, 0);
  world.objects_.push_back(shape);
  utility::Ray ray = utility::Ray(
      utility::Point(0, 0, -3), utility::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  geometry::Intersection intersection(sqrt(2), shape);

  geometry::Computations comps = intersection.PrepareComputations(ray);
  utility::Color color = world.ShadeHit(comps);

  EXPECT_TRUE(utility::Color(0.87675770936104, 0.92434078945592,
                             0.82917462926615) == color);
}

TEST(WorldTest, ColorAtWithMutuallyReflectiveSurfaces) {
  scene::World world;

  std::shared_ptr<scene::PointLight> light =
      std::make_shared<scene::PointLight>(
          scene::PointLight(utility::Point(0, 0, 0), utility::Color(1, 1, 1)));
  world.light_sources_.push_back(light);

  std::shared_ptr<geometry::Plane> lower = std::make_shared<geometry::Plane>();
  lower->material_.reflective_ = 1;
  lower->transform_ = utility::Translation(0, -1, 0);
  world.objects_.push_back(lower);

  std::shared_ptr<geometry::Plane> upper = std::make_shared<geometry::Plane>();
  upper->material_.reflective_ = 1;
  upper->transform_ = utility::Translation(0, 1, 0);
  world.objects_.push_back(upper);

  utility::Ray ray =
      utility::Ray(utility::Point(0, 0, 0), utility::Vector(0, 1, 0));

  world.ColorAt(ray); // Should terminate successfully
}

TEST(WorldTest, TheReflectedColorAtTheMaximumRecursiveDepth) {
  scene::World world = scene::DefaultWorld();
  std::shared_ptr<geometry::Plane> shape = std::make_shared<geometry::Plane>();
  shape->material_.reflective_ = 0.5;
  shape->transform_ = utility::Translation(0, -1, 0);
  world.objects_.push_back(shape);
  utility::Ray ray = utility::Ray(
      utility::Point(0, 0, -3), utility::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  geometry::Intersection intersection(sqrt(2), shape);

  geometry::Computations comps = intersection.PrepareComputations(ray);
  utility::Color color = world.ReflectedColor(comps, 0);

  EXPECT_TRUE(utility::Color(0, 0, 0) == color);
}