#ifndef FILE_COLLISION_DETECTOR_HPP
#define FILE_COLLISION_DETECTOR_HPP

/**
Inspector Collision Detector
           ___
     _..--"\  `|`""--.._
  .-'       \  |        `'-.
 /           \_|___...----'`\
|__,,..--""``(_)--..__      |
'\     _.--'`.I._     ''--..'
  `''"`,#JGS/_|_\###,---'`
    ,#'  _.:`___`:-._ '#,
   #'  ,~'-;(oIo);-'~, '#
   #   `~-(  |    )=~`  #
   #       | |_  |      #
   #       ; ._. ;      #
   #  _..-;|\ - /|;-._  #
   #-'   /_ \\_// _\  '-#
 /`#    ; /__\-'__\;    #`\
;  #\.--|  |O  O   |'-./#  ;
|__#/   \ _;O__O___/   \#__|
 | #\    [I_[_]__I]    /# |
 \_(#   /  |O  O   \   #)_/
       /   |        \
      /    |         \
     /    /\          \
    /     | `\         ;
   ;      \   '.       |
    \-._.__\     \_..-'/
     '.\  \-.._.-/  /'`
        \_.\    /._/
         \_.;  ;._/
       .-'-./  \.-'-.
      (___.'    '.___)
 **/

#include <memory>
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/enum/axis.hpp"
#include "brickengine/enum/direction.hpp"

struct CollisionReturnValues {
    CollisionReturnValues(double spaceLeft, int objectId, bool isTrigger) : spaceLeft(spaceLeft), objectId(objectId), isTrigger(isTrigger) {}
    double spaceLeft;
    int objectId;
    bool isTrigger;
};

struct TriggerReturnValues {
    TriggerReturnValues(bool isInTrigger, std::optional<int> objectId) : isInTrigger(isInTrigger), objectId(objectId) {}
    bool isInTrigger;
    std::optional<int> objectId;
};

class CollisionDetector {
public:
		CollisionDetector(std::shared_ptr<EntityManager> em);
		// Returns amount of pixels that can still be moved to the collidable object.
		CollisionReturnValues spaceLeft(int entity, Axis axis, Direction direction);
    TriggerReturnValues isInTrigger(int entity);
private:
		std::shared_ptr<EntityManager> entityManager;
};

#endif // FILE_COLLISION_DETECTOR_HPP