#ifndef FILE_COLLISION_COMPONENT_HPP
#define FILE_COLLISION_COMPONENT_HPP

#include "brickengine/components/component.hpp"

class CollisionComponent : public Component {
public:
    CollisionComponent(double x, double y): x(x), y(y) { };
    CollisionComponent() : x(0), y(0) { };
	std::string getName() {
		return "CollisionComponent";
	};
    double x;
    double y;
};

#endif