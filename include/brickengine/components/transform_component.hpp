#ifndef FILE_TRANSFORM_HPP
#define FILE_TRANSFORM_HPP

#include "brickengine/components/component_impl.hpp"

class TransformComponent : public ComponentImpl<TransformComponent> {
public:
    TransformComponent(double xPos, double yPos, double xScale, double yScale);
    static std::string getNameStatic();

    // Getters and Setters
    void setXPos(double x);
    double getXPos() const;
    void setYPos(double y);
    double getYPos() const;

    void setXScale(double s);
    double getXScale() const;
    void setYScale(double s);
    double getYScale() const;
private:
    double xPos;
    double yPos;
    double xScale;
    double yScale;
};

#endif /* FILE_TRANSFORM_HPP */