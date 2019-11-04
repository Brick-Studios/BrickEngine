#ifndef FILE_PHYSICS_COMPONENT_HPP
#define FILE_PHYSICS_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class PhysicsComponent : public ComponentImpl<PhysicsComponent> {
public:
    PhysicsComponent(double mass, double drag, double vx, double vy, bool gravity,
                     bool kinematic, bool flipXDirection, bool flipYDirection);
    static std::string getNameStatic();

    // Data
    double mass;
    double drag;
    double vx;
    double vy;
    bool gravity;
    bool kinematic;
    bool flipXDirection;
    bool flipYDirection;
};

#endif // FILE_PHYSICS_COMPONENT