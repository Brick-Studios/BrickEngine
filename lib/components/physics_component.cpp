#include "brickengine/components/physics_component.hpp"

PhysicsComponent::PhysicsComponent(double mass, bool drag, double vx, double vy, bool gravity,
                                   Kinematic kinematic, bool flipX, bool flipY)
    : mass(mass), drag(drag), vx(vx), vy(vy), gravity(gravity), kinematic(kinematic),
    flipX(flipX), flipY(flipY)  {}

std::string PhysicsComponent::getNameStatic() {
    return "PhysicsComponent";
}