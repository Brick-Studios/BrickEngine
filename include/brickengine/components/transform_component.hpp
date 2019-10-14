#ifndef FILE_TRANSFORM_HPP
#define FILE_TRANSFORM_HPP

#include "brickengine/components/component_impl.hpp"

class TransformComponent : public ComponentImpl<TransformComponent> {
public:
    TransformComponent(double xPos, double yPos, double xScale, double yScale);
    static std::string getNameStatic();

    // Data
    double xPos;
    double yPos;
    double xScale;
    double yScale;
};

#endif /* FILE_TRANSFORM_HPP */