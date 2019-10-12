#ifndef FILE_LINE_HPP
#define FILE_LINE_HPP

#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/data/color.hpp"
#include "brickengine/rendering/renderer.hpp"

class Renderer;

class Line : public Renderable {
public:
    Line(int x1, int y1, int x2, int y2, Color color, int layer);
    void render(Renderer& r);
    int getX1() const;
    int getY1() const;
    int getX2() const;
    int getY2() const;
    Color getColor() const;
private:
    int x1, y1;
    int x2, y2;
    Color color;
};

#endif // FILE_LINE_HPP