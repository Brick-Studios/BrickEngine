#ifndef FILE_SQUARE_COLLISION_COMPONENT_HPP
#define FILE_SQUARE_COLLISION_COMPONENT_HPP

#include "brickengine/components/collision/collision_component.hpp"

class SquareCollisionComponent : public CollisionComponent {
public:
	SquareCollisionComponent(double x, double y, double w, double h) : CollisionComponent(x, y), w(w), h(h) {};
    SquareCollisionComponent(): w(0), h(0) { };
	std::string getName() {
		return "SquareCollisionComponent";
	};
    double w;
    double h;
};

#endif