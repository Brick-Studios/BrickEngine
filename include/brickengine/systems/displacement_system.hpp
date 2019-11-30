#ifndef FILE_DISPLACEMENT_SYSTEM_HPP
#define FILE_DISPLACEMENT_SYSTEM_HPP

#include "brickengine/systems/system.hpp"
#include "brickengine/collision_detector_2.hpp"
#include <vector>
#include <unordered_map>

class DisplacementSystem : public System {
public:
    DisplacementSystem(std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions, CollisionDetector2& cd, std::shared_ptr<EntityManager> em);
    bool findDisplacementException(std::set<std::string> tags_1, std::set<std::string> tags_2);
    void update(double deltatime);
private:
    CollisionDetector2& collision_detector;
    std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions;
};

#endif // FILE_DISPLACEMENT_SYSTEM_HPP