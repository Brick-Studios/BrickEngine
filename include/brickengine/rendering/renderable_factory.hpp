#ifndef FILE_RENDERABLE_FACTORY_HPP
#define FILE_RENDERABLE_FACTORY_HPP

#include "brickengine/rendering/renderables/texture.hpp"
#include "brickengine/rendering/renderables/data/rect.hpp"
#include "brickengine/rendering/renderables/data/color.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/resource_manager.hpp"

#include <memory>

class RenderableFactory{
public:
    RenderableFactory(std::shared_ptr<Renderer> r, std::shared_ptr<ResourceManager> rm);
    std::unique_ptr<Texture> createText(std::string text, int font_size, Color color, int layer, std::unique_ptr<Rect> dst) const;
    // dst = where the image should be drawn
    std::unique_ptr<Texture> createImage(std::string path, int layer, std::unique_ptr<Rect> dst) const;
    // dst = where the image should be drawn
    // src = what part of the image should be drawn
    std::unique_ptr<Texture> createImage(std::string path, int layer, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src) const;
    std::unique_ptr<Circle> createCircle(int x, int y, int radius, bool filled, Color color, int layer) const;
    std::unique_ptr<Line> createLine(int x1, int y1, int x2, int y2, Color color, int layer) const;
private:
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<ResourceManager> resource_manager;
};

#endif // FILE_RENDERABLE_FACTORY_HPP
