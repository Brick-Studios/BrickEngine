#ifndef FILE_DISPLACEMENT_SYSTEM_HPP
#define FILE_DISPLACEMENT_SYSTEM_HPP

#include "brickengine/systems/system.hpp"
#include "brickengine/collision_detector_2.hpp"

class DisplacementSystem : public System {
public:
    DisplacementSystem(std::shared_ptr<EntityManager> em, CollisionDetector2& cd);
    void update(double deltatime);
private:
    CollisionDetector2& collision_detector;
};

#endif // FILE_DISPLACEMENT_SYSTEM_HPP