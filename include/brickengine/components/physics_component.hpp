#ifndef FILE_PHYSICS_COMPONENT_HPP
#define FILE_PHYSICS_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"
#include "brickengine/components/enums/kinematic.hpp"

class PhysicsComponent : public ComponentImpl<PhysicsComponent> {
public:
    PhysicsComponent(double mass, bool drag, double vx, double vy, bool gravity,
                     Kinematic kinematic, bool flipX, bool flipY);
    static std::string getNameStatic();

    // Data
    double mass;
    bool drag;
    double vx;
    double vy;
    bool gravity;
    Kinematic kinematic;
    // If the entity is a parent, only the direction will get flipped
    // If the entity is a child, both the direction and position get flipped
    bool flipX;
    bool flipY;
};

#endif // FILE_PHYSICS_COMPONENT
