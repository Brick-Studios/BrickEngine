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
    CollisionReturnValues(double space_left, std::optional<int> object_id, bool is_trigger) : space_left(space_left), object_id(object_id), is_trigger(is_trigger) {}
    double space_left;
    std::optional<int> object_id;
    bool is_trigger;
};

struct TriggerReturnValues {
    TriggerReturnValues(bool is_in_trigger, std::optional<int> object_id) : is_in_trigger(is_in_trigger), object_id(object_id) {}
    bool is_in_trigger;
    std::optional<int> object_id;
};

class CollisionDetector {
public:
		CollisionDetector(std::shared_ptr<EntityManager> em);
		// Returns amount of pixels that can still be moved to the collidable object.
		CollisionReturnValues spaceLeft(int entity, Axis axis, Direction direction);
    TriggerReturnValues isInTrigger(int entity);
private:
		std::shared_ptr<EntityManager> entity_manager;
};

#endif // FILE_COLLISION_DETECTOR_HPP