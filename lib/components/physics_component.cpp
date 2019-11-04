#include "brickengine/components/physics_component.hpp"

PhysicsComponent::PhysicsComponent(double mass, double drag, double vx, double vy, bool gravity,
                                   bool kinematic, bool flipXDirection, bool flipYDirection)
    : mass(mass), drag(drag), vx(vx), vy(vy), gravity(gravity), kinematic(kinematic),
    flipXDirection(flipXDirection), flipYDirection(flipYDirection)  {}

std::string PhysicsComponent::getNameStatic() {
    return "PhysicsComponent";
}