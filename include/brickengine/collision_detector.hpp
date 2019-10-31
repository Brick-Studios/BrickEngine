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
#include "brickengine/collision_return_values.hpp"

class CollisionDetector {
public:
		CollisionDetector(std::shared_ptr<EntityManager> em);
		// Returns amount of pixels that can still be moved to the collidable object.
		collisionReturnValues spaceLeft(int entity, Axis axis, Direction direction);
    		triggerReturnValues isInTrigger(int entity);
private:
		std::shared_ptr<EntityManager> entityManager;
};
#endif // FILE_COLLISION_DETECTOR_HPP
