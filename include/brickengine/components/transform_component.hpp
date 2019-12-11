#ifndef FILE_TRANSFORM_HPP
#define FILE_TRANSFORM_HPP

#include "brickengine/components/component_impl.hpp"
#include "brickengine/enum/direction.hpp"

class TransformComponent : public ComponentImpl<TransformComponent> {
public:
    TransformComponent(double x_pos, double y_pos, double x_scale, double y_scale, Direction x_direction, Direction y_direction);
    static std::string getNameStatic();

    // Data
    double x_pos;
    double y_pos;
    double x_scale;
    double y_scale;
    Direction x_direction;
    Direction y_direction;
};

#endif // FILE_TRANSFORM_HPP
