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

struct EntityWithIsTrigger {
    EntityWithIsTrigger(int id, bool is_trigger) : id(id), is_trigger(is_trigger) {}
    int id;
    bool is_trigger;
};

struct DiscreteCollision {
    DiscreteCollision(EntityWithIsTrigger entity, EntityWithIsTrigger opposite)
        : entity(entity), opposite(opposite) {}
    EntityWithIsTrigger entity;
    EntityWithIsTrigger opposite;
};

struct ContinuousCollision {
    ContinuousCollision(EntityWithIsTrigger entity, std::optional<EntityWithIsTrigger> opposite, double space_left)
        : entity(entity), opposite(opposite), space_left(space_left) {}
    EntityWithIsTrigger entity;
    std::optional<EntityWithIsTrigger> opposite;
    double space_left;
};

class CollisionDetector2 {
public:
    CollisionDetector2(EntityManager& em) : em(em) {};

    std::vector<DiscreteCollision> detectDiscreteCollision(int entity_id);
    ContinuousCollision detectContinuousCollision(int entity_id, Axis axis, Direction direction);
private:
    EntityManager& em;
};

#endif // FILE_COLLISION_DETECTOR_2_HPP