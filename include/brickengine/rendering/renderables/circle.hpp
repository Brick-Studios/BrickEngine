#ifndef FILE_CIRCLE_HPP
#define FILE_CIRCLE_HPP

#include "brickengine/rendering/renderables/clone_renderable.hpp"
#include "brickengine/rendering/renderables/circle.hpp"
#include "brickengine/rendering/renderer.hpp"

class Renderer;

class Circle : public CloneRenderable {
public:
    Circle(int x, int y, int radius, bool filled, Color color, int layer);
    void render(Renderer& r);
    int getX() const;
    int getY() const;
    int getRadius() const;
    bool getFilled() const;
    Color getColor() const;
    std::unique_ptr<CloneRenderable> clone();
private:
    int x, y;
    int radius;
    bool filled;
    Color color;
};

#endif // FILE_CIRCLE_HPP