#ifndef FILE_DISPLACEMENT_SYSTEM_HPP
#define FILE_DISPLACEMENT_SYSTEM_HPP

#include "brickengine/systems/system.hpp"
#include "brickengine/collision_detector_2.hpp"
#include <vector>
#include <unordered_map>

class DisplacementSystem : public System {
public:
    DisplacementSystem(CollisionDetector2& cd, std::shared_ptr<EntityManager> em);
    void update(double deltatime);
private:
    CollisionDetector2& collision_detector;
};

#endif // FILE_DISPLACEMENT_SYSTEM_HPP