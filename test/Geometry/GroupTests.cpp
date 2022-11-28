#include "Group.hpp"

#include <gtest/gtest.h>

#include "Sphere.hpp"

using namespace raytracer;
using namespace utility;

TEST(GroupTest, CreatingANewGroup) {
  auto group = std::make_shared<geometry::Group>();
  EXPECT_TRUE(Identity() == group->transform_);
  EXPECT_TRUE(group->children_.empty());
}

TEST(GroupTest, AddingAChildToAGroup) {
  auto group = std::make_shared<geometry::Group>();
  auto shape = std::make_shared<geometry::TestShape>();
  group->AddChild(shape);
  EXPECT_FALSE(group->children_.empty());
  EXPECT_TRUE(std::find(group->children_.begin(), group->children_.end(),
                        shape) != group->children_.end());
  EXPECT_EQ(group.get(), shape->parent_);
}

TEST(GroupTest, IntersectingARayWithAnEmptyGroup) {
  auto group = std::make_shared<geometry::Group>();
  auto ray = Ray(Point(0, 0, 0), Vector(0, 0, 1));
  auto xs = group->LocalIntersect(ray);
  EXPECT_TRUE(xs.empty());
}

TEST(GroupTest, IntersectingARayWithANonemptyGroup) {
  auto group = std::make_shared<geometry::Group>();
  auto sphere1 = std::make_shared<geometry::Sphere>();
  auto sphere2 = std::make_shared<geometry::Sphere>();
  sphere2->SetTransform(Translation(0, 0, -3));
  auto sphere3 = std::make_shared<geometry::Sphere>();
  sphere3->SetTransform(Translation(5, 0, 0));

  group->AddChild(sphere1);
  group->AddChild(sphere2);
  group->AddChild(sphere3);

  auto ray = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  auto xs = group->LocalIntersect(ray);

  EXPECT_EQ(4, xs.size());
  EXPECT_EQ(sphere2->id_, xs[0].object_->id_);
  EXPECT_EQ(sphere2->id_, xs[1].object_->id_);
  EXPECT_EQ(sphere1->id_, xs[2].object_->id_);
  EXPECT_EQ(sphere1->id_, xs[3].object_->id_);
}

TEST(GroupTest, IntersectingATransformedGroup) {
  auto group = std::make_shared<geometry::Group>();
  group->SetTransform(Scaling(2, 2, 2));
  auto sphere = std::make_shared<geometry::Sphere>();
  sphere->SetTransform(Translation(5, 0, 0));

  group->AddChild(sphere);

  auto ray = Ray(Point(10, 0, -10), Vector(0, 0, 1));
  auto xs = group->Intersect(ray);

  EXPECT_EQ(2, xs.size());
}