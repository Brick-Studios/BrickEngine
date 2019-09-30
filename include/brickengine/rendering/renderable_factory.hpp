#ifndef FILE_RENDERABLE_FACTORY_HPP
#define FILE_RENDERABLE_FACTORY_HPP

#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/rect.hpp"
#include "brickengine/rendering/renderer.hpp"

#include <memory>

class RenderableFactory{
public:
    RenderableFactory(std::shared_ptr<Renderer> r);
    std::unique_ptr<Renderable> createImage(std::string path, int layer, std::unique_ptr<Rect> dst) const;
    std::unique_ptr<Renderable> createImage(std::string path, int layer, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src) const;
private:
    std::shared_ptr<Renderer> renderer;
    SDL_Texture* createBMPTexture(std::string path) const;
};

#endif