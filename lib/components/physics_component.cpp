#include "brickengine/components/physics_component.hpp"

PhysicsComponent::PhysicsComponent(double mass, double drag, double vx, double vy, bool gravity, bool kinematic)
                    : mass(mass), drag(drag), vx(vx), vy(vy), gravity(gravity), kinematic(kinematic)  {}

std::string PhysicsComponent::getNameStatic() {
    return "PhysicsComponent";
}

// Getters and Setters
void PhysicsComponent::setMass(double m) {
    this->mass = m;
}
double PhysicsComponent::getMass() const {
    return mass;
}
void PhysicsComponent::setDrag(double d) {
    this->drag = d;
}
double PhysicsComponent::getDrag() const {
    return drag;
}
void PhysicsComponent::setXVelocity(double v) {
    this->vx = v;
}
double PhysicsComponent::getXVelocity() const {
    return vx;
}
void PhysicsComponent::setYVelocity(double v) {
    this->vy = v;
}
double PhysicsComponent::getYVelocity() const {
    return vy;
}
void PhysicsComponent::setGravity(bool g) {
    this->gravity = g;
}
bool PhysicsComponent::getGravity() const {
    return gravity;
}
void PhysicsComponent::setKinematic(bool k){
    this->kinematic = k;
}
bool PhysicsComponent::getKinematic() const{
    return kinematic;
}