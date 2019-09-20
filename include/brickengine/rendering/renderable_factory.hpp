#ifndef FILE_RENDERABLE_FACTORY_HPP
#define FILE_RENDERABLE_FACTORY_HPP

#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderer.hpp"

#include <memory>

class RenderableFactory{
public:
    RenderableFactory(std::shared_ptr<Renderer> r);
    std::unique_ptr<Renderable> createImage(std::string path);
    std::unique_ptr<Renderable> createAnimation(std::string path, int frames, int speed);
private:
    std::shared_ptr<Renderer> renderer;
};

#endif