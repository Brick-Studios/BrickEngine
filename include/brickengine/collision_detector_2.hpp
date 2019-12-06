#ifndef FILE_COLLISION_DETECTOR_2_HPP
#define FILE_COLLISION_DETECTOR_2_HPP

#include <memory>
#include <vector>
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/enum/axis.hpp"
#include "brickengine/enum/direction.hpp"

/* Collision Detector 2
   Also better known as:
   - The one that replaces the old Collision Detector
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

struct Collision {
    Collision(int opposite_id, bool is_trigger) : opposite_id(opposite_id), is_trigger(is_trigger) {}
    int opposite_id;
    bool is_trigger;
};

struct DiscreteCollision {
    DiscreteCollision(int opposite_id, bool is_trigger,
                      Position position, Position delta, Position normal)
        : opposite_id(opposite_id), is_trigger(is_trigger),
          position(position), delta(delta), normal(normal) {}
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
    ContinuousCollision(std::optional<int> opposite_id, double space_left)
        : opposite_id(opposite_id), space_left(space_left) {}
    std::optional<int> opposite_id;
    double space_left;
};

struct CollisionDetector2CacheInfo {
    int discrete_calculated_counter;
    int discrete_cache_hits;
    int continuous_calculations_counter;
    int continuous_cache_hits;
};

class CollisionDetector2 {
public:
    CollisionDetector2(std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions, EntityManager& em);
    bool hasTriggerException(std::set<std::string> tags_1, std::set<std::string> tags_2) const;
    std::vector<DiscreteCollision> detectDiscreteCollision(int entity_id);
    ContinuousCollision detectContinuousCollision(int entity_id, Axis axis, Direction direction);
    std::vector<Collision> detectCollision(int entity_id);

    // This returns a copy of the cache info
    CollisionDetector2CacheInfo getCacheInfo() const;
    void invalidateCache();
private:
    EntityManager& em;
    // Trigger exceptions that you still want collidable, left tag will collide with right tag.
    std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions;

    // Cache
    std::unordered_map<int, std::vector<DiscreteCollision>> discrete_cache;
    std::unordered_map<int, std::unordered_map<Axis, std::unordered_map<Direction, ContinuousCollision>>> continuous_cache;
    CollisionDetector2CacheInfo cache_info;
};

#endif // FILE_COLLISION_DETECTOR_2_HPP
