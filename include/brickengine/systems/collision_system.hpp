#ifndef FILE_COLLISION_SYSTEM_HPP
#define FILE_COLLISION_SYSTEM_HPP

#include "brickengine/entities/entity_manager.hpp"

#include "brickengine/enum/axis.hpp"
#include "brickengine/enum/direction.hpp"

class CollisionSystem {

public:
    CollisionSystem(EntityManager* entityManager);
    //Returns amount of pixels that can still be moved to the collidable object.
    double canMove(int entity, Axis axis, Direction direction);
private:
    EntityManager* entityManager;
};
#endif