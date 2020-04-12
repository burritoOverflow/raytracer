#include "World.h"

#include <algorithm>
#include <gtest/gtest.h>

using namespace raytracer;

TEST(WorldTests, CreateWorld) {
  scene::World w;
  ASSERT_EQ(0, w.objects_.size());
  ASSERT_EQ(0, w.light_sources_.size());
}

TEST(WorldTests, DefaultWorld) {
  scene::PointLight light(utility::Point(-10, 10, -10),
                          utility::Color(1, 1, 1));
  std::shared_ptr<geometry::Sphere> s1 = std::make_shared<geometry::Sphere>();
  s1->material_ =
      material::Material(utility::Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200);
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

TEST(WorldTests, IntersectWorldWithRay) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::vector<geometry::Intersection> xs = w.Intersect(r);
  ASSERT_EQ(4, xs.size());
  EXPECT_TRUE(4 == xs[0].t_);
  EXPECT_TRUE(4.5 == xs[1].t_);
  EXPECT_TRUE(5.5 == xs[2].t_);
  EXPECT_TRUE(6 == xs[3].t_);
}

TEST(WorldTests, ShadeIntersection) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  std::shared_ptr<geometry::Shape> shape = w.objects_.front();
  geometry::Intersection i(4, shape);
  geometry::Computations comps = i.PrepareComputations(r);
  utility::Color c = w.ShadeHit(comps);
  EXPECT_TRUE(utility::Color(0.38066119308103435, 0.47582649135129296,
                             0.28549589481077575) == c);
}

TEST(WorldTests, ShadeIntersectionFromTheInside) {
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

TEST(WorldTests, TheColorWhenRayMisses) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 1, 0));
  utility::Color c = w.ColorAt(r);
  EXPECT_TRUE(utility::Color(0, 0, 0) == c);
}

TEST(WorldTests, TheColorWhenRayHits) {
  scene::World w = scene::DefaultWorld();
  utility::Ray r(utility::Point(0, 0, -5), utility::Vector(0, 0, 1));
  utility::Color c = w.ColorAt(r);
  EXPECT_TRUE(utility::Color(0.38066119308103435, 0.47582649135129296,
                             0.28549589481077575) == c);
}

TEST(WorldTests, TheColorWithIntersectionBehindTheRay) {
  scene::World w = scene::DefaultWorld();

  auto outer = w.objects_.front();
  outer->material_.ambient_ = 1;

  auto inner = w.objects_.at(1);
  inner->material_.ambient_ = 1;

  utility::Ray r(utility::Point(0, 0, 0.75), utility::Vector(0, 0, -1));
  utility::Color c = w.ColorAt(r);
  EXPECT_TRUE(inner->material_.color_ == c);
}

TEST(WorldTests, ThereIsNoShadowWhenNothingIsCollinearWithPointAndLight) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(0, 10, 0);
  EXPECT_FALSE(w.IsShadowed(p));
}

TEST(WorldTests, TheShadowWhenAnObjectIsBetweenThePointAndTheLight) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(10, -10, 10);
  EXPECT_TRUE(w.IsShadowed(p));
}

TEST(WorldTests, ThereIsNoShadowWhenAnObjectIsBehindTheLight) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(-20, 20, -20);
  EXPECT_FALSE(w.IsShadowed(p));
}

TEST(WorldTests, ThereIsNoShadowWhenAnObjectIsBehindThePoint) {
  scene::World w = scene::DefaultWorld();
  utility::Point p(-2, 2, -2);
  EXPECT_FALSE(w.IsShadowed(p));
}

TEST(WorldTests, TheShadeHitFunctionIsGivenAnIntersectionInShadow) {
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
