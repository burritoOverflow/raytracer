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
  geometry::Sphere s1;
  s1.material_ =
      material::Material(utility::Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200);
  geometry::Sphere s2;
  s2.transform_ = utility::Scaling(0.5, 0.5, 0.5);
  scene::World w = scene::DefaultWorld();

  // The initialization of the world will also increment the ids, which is used
  // for comparison. Therefore, we increment the ids by 2.
  s1.id_ += 2;
  s2.id_ += 2;

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