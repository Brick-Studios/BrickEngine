#ifndef FILE_PHYSICS_COMPONENT_HPP
#define FILE_PHYSICS_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class PhysicsComponent : public ComponentImpl<PhysicsComponent> {
public:
    PhysicsComponent(double mass, double drag, double vx, double vy, bool gravity, bool kinematic);
    static std::string getNameStatic();

    // Data
    double mass;
    double drag;
    double vx;
    double vy;
    bool gravity;
    bool kinematic;
};

#endif // FILE_PHYSICS_COMPONENT