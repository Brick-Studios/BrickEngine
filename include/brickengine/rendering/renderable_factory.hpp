#ifndef FILE_RENDERABLE_FACTORY_HPP
#define FILE_RENDERABLE_FACTORY_HPP

#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/rect.hpp"
#include "brickengine/rendering/renderer.hpp"

#include <memory>

class RenderableFactory{
public:
    RenderableFactory(std::shared_ptr<Renderer> r);
    ~RenderableFactory();
    std::unique_ptr<Renderable> createImage(std::string path, std::unique_ptr<Rect> dst) const;
    std::unique_ptr<Renderable> createImage(std::string path, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src) const;
    // std::unique_ptr<Renderable> createAnimation(std::string path, int frames, int speed) const; //TODO dit nog aanvullen (zie Animation.cpp)
private:
    std::shared_ptr<Renderer> renderer;
    SDL_Texture* createBMPTexture(std::string path) const;
};

#endif