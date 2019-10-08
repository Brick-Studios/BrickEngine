#ifndef FILE_COLLISION_COMPONENT_HPP
#define FILE_COLLISION_COMPONENT_HPP

#include "brickengine/components/component.hpp"

class CollisionComponent : public Component {
public:
    CollisionComponent(double x, double y, int z, int vz): x(x), y(y), z(z), vz(vz) { };
    CollisionComponent() : x(0), y(0), z(0), vz(0) { };
	std::string getName() {
		return "CollisionComponent";
	};
    double x;
    double y;
	int z;
	int vz; //The amount of extra layers the collidable stretces to
};

#endif