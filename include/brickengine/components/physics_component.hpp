#ifndef FILE_PHYSICS_COMPONENT_HPP
#define FILE_PHYSICS_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class PhysicsComponent : public ComponentImpl<PhysicsComponent> {
public:
    PhysicsComponent(double mass, double drag, double vx, double vy, bool gravity, bool kinematic);
    static std::string getNameStatic();

    // Getters and Setters
    void setMass(double mass);
    double getMass() const;
    
    void setDrag(double drag);
    double getDrag() const;
    
    void setXVelocity(double vx);
    double getXVelocity() const;

    void setYVelocity(double vy);
    double getYVelocity() const;

    void setGravity(bool useGravity);
    bool getGravity() const;
    
    void setKinematic(bool isKinematic);
    bool getKinematic() const;
private:
    double mass;
    double drag;
    double vx;
    double vy;
    bool gravity;
    bool kinematic;
};

#endif // FILE_PHYSICS_COMPONENT