#include "brickengine/rendering/renderables/line.hpp"

Line::Line(int x1, int y1, int x2, int y2, Color color, int layer) :
           Renderable(layer),
           x1(x1), y1(y1), x2(x2), y2(y2), color(color) {}

void Line::render(Renderer& r) {
    r.render(*this);
}

// Getters
int Line::getX1() const {
    return x1;
}
int Line::getY1() const {
    return y1;
}
int Line::getX2() const {
    return x2;
}
int Line::getY2() const {
    return y2;
}
Color Line::getColor() const {
    return color;
}