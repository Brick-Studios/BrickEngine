#include "brickengine/rendering/renderable_factory.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderables/renderable.hpp"

#include <memory>
#include <string>

RenderableFactory::RenderableFactory(std::shared_ptr<Renderer> r){
    this->renderer = r;
}

std::unique_ptr<Renderable> RenderableFactory::createImage(std::string path){
    return nullptr;
}

std::unique_ptr<Renderable> RenderableFactory::createAnimation(std::string path, int frames, int speed){
    return nullptr;
}