#include "brickengine/rendering/renderables/circle.hpp"

Circle::Circle(int x, int y, int radius, bool filled, Color color, int layer) :
               Renderable(layer), x(x), y(y), radius(radius), filled(filled), color(color) {}

void Circle::render(Renderer& r) {
    r.render(*this);
}

// Getters
int Circle::getX() const {
    return x;
}
int Circle::getY() const {
    return y;
}
int Circle::getRadius() const {
    return radius;
}
bool Circle::getFilled() const {
    return filled;
}
Color Circle::getColor() const {
    return color;
}