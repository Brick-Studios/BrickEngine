#ifndef FILE_COLLISION_DETECTOR_2_HPP
#define FILE_COLLISION_DETECTOR_2_HPP

#include <memory>
#include <vector>
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/enum/axis.hpp"
#include "brickengine/enum/direction.hpp"

/* Collision Detector 2
   Also better known as:
   - Collision II
   - Inspector Collision Detector 2
   - The Sequel
   - The superior version
   - The one that Luuk didn't write
   - The Mao Zedong of dictators
   - The younger but better brother
   - The Chamber of Collisions
   - Collision Wars - The Collision Strikes Back
   - Collision Park - The Lost Collisions
   - The Collisions Reloaded
   - Age of Collisions
   - Collision Wars - The Last Collision
   - The Lord of the Collisions - The 2 Collisions
   - Collision harder
   - Mad Collision - The Collision Warrior
   - Collision Day
   - 2 Collisions 2 Furious
   - Collision Resurrection
   - Alien vs Collision
   - Final Collision 2
   - The Incredible Collision
   - Collision Returns
   - The Dark Collision
   - Indiana Jones and the Temple of Collisions
*/

struct DiscreteCollision {
    DiscreteCollision(int entity_id, int opposite_id, bool is_trigger,
                      Position position, Position delta, Position normal)
        : entity_id(entity_id), opposite_id(opposite_id), is_trigger(is_trigger),
          position(position), delta(delta), normal(normal) {}
    int entity_id;
    int opposite_id;
    bool is_trigger;

    // The point of contact between the two objects
    Position position;
    // The overlap between the two objects, and is a vector that can be added
    // to the colliding object’s position to move it back to a non-colliding state
    Position delta;
    // The surface normal at the point of contact
    Position normal;
};

struct ContinuousCollision {
    ContinuousCollision(int entity_id, std::optional<int> opposite_id, bool is_trigger, double space_left)
        : entity_id(entity_id), opposite_id(opposite_id), is_trigger(is_trigger), space_left(space_left) {}
    int entity_id;
    std::optional<int> opposite_id;
    bool is_trigger;
    double space_left;
};

class CollisionDetector2 {
public:
    CollisionDetector2(std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions, EntityManager& em);
    bool findDisplacementException(std::set<std::string> tags_1, std::set<std::string> tags_2);
    std::vector<DiscreteCollision> detectDiscreteCollision(int entity_id);
    ContinuousCollision detectContinuousCollision(int entity_id, Axis axis, Direction direction);
private:
    EntityManager& em;
    std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions;
};

#endif // FILE_COLLISION_DETECTOR_2_HPP