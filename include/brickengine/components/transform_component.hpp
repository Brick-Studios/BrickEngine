#ifndef FILE_TRANSFORM_HPP
#define FILE_TRANSFORM_HPP

#include "brickengine/components/component_impl.hpp"
#include "brickengine/enum/direction.hpp"

class TransformComponent : public ComponentImpl<TransformComponent> {
public:
    TransformComponent(double xPos, double yPos, double xScale, double yScale, Direction xDirection, Direction yDirection);
    static std::string getNameStatic();

    // Data
    double xPos;
    double yPos;
    double xScale;
    double yScale;
    Direction xDirection;
    Direction yDirection;
};

#endif // FILE_TRANSFORM_HPP
