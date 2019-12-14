#ifndef FILE_PHYSICS_COMPONENT_HPP
#define FILE_PHYSICS_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"
#include "brickengine/components/enums/kinematic.hpp"

class CollisionDetectionType {
public:
    CollisionDetectionType(bool discrete, bool continuous) : discrete(discrete), continuous(continuous) {}
    bool isDiscrete() const { return discrete; }
    bool isContinuous() const { return continuous; }
    bool isBoth() const { return discrete && continuous; }
private:
    bool discrete;
    bool continuous;
};

class PhysicsComponent : public ComponentImpl<PhysicsComponent> {
public:
    PhysicsComponent(double mass, bool drag, double vx, double vy, bool gravity,
                     Kinematic kinematic, bool flipX, bool flipY, CollisionDetectionType collision_detection);
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
    CollisionDetectionType collision_detection;
};

#endif // FILE_PHYSICS_COMPONENT
