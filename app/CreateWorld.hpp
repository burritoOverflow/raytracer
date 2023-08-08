#define _USE_MATH_DEFINES

#include <cmath>

#include "CheckersPattern.hpp"
#include "Cylinder.hpp"
#include "GradientPattern.hpp"
#include "Group.hpp"
#include "Matrix.hpp"
#include "Plane.hpp"
#include "RingPattern.hpp"
#include "Sphere.hpp"
#include "StripePattern.hpp"
#include "World.hpp"

std::shared_ptr<raytracer::geometry::Sphere> HexagonCorner() {
    auto corner = std::make_shared<raytracer::geometry::Sphere>();
    corner->transform_ =
            raytracer::utility::Scaling(0.25, 0.25, 0.25).Translate(0, 0, -1);
    return corner;
}

std::shared_ptr<raytracer::geometry::Cylinder> HexagonEdge() {
    auto edge = std::make_shared<raytracer::geometry::Cylinder>();
    edge->minimum_ = 0;
    edge->maximum_ = 1;
    edge->transform_ = raytracer::utility::Scaling(0.25, 1, 0.25)
            .RotateZ(-M_PI_2)
            .RotateY(-M_PI / 6)
            .Translate(0, 0, -1);
    return edge;
}

std::shared_ptr<raytracer::geometry::Group> HexagonSide() {
    auto side = std::make_shared<raytracer::geometry::Group>();
    side->AddChild(HexagonCorner());
    side->AddChild(HexagonEdge());
    return side;
}

std::shared_ptr<raytracer::geometry::Group> Hexagon() {
    auto hexagon = std::make_shared<raytracer::geometry::Group>();
    for (size_t n = 0; n < 6; ++n) {
        auto side = HexagonSide();
        side->transform_ = raytracer::utility::RotationY(n * M_PI / 3);
        hexagon->AddChild(side);
    }
    return hexagon;
}

inline raytracer::scene::World CreateWorld() {
    raytracer::scene::World world;

    world.objects_.push_back(Hexagon());

    // Add a white light source, shining from above and to the left
    world.light_sources_.push_back(std::make_shared<raytracer::scene::PointLight>(
            raytracer::scene::PointLight(raytracer::utility::Point(-10, 10, -10),
                                         raytracer::utility::Color(1, 1, 1))));

    return world;
}