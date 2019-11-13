#include <memory>
#include <string>
#include <iostream>
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "brickengine/rendering/renderable_factory.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/texture.hpp"
#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderables/data/rect.hpp"
    
RenderableFactory::RenderableFactory(std::shared_ptr<Renderer> r, std::shared_ptr<ResourceManager> rm)
    : renderer(r), resource_manager(rm) {}

std::unique_ptr<Texture> RenderableFactory::createImage(std::string path, int layer, std::unique_ptr<Rect> dst, int alpha) const {
    auto shared_texture = resource_manager->getTexture(path);
    SDL_SetTextureBlendMode(shared_texture.get(), SDL_BLENDMODE_BLEND);

    return std::make_unique<Texture>(std::move(shared_texture), layer, alpha, std::move(dst));
}

std::unique_ptr<Texture> RenderableFactory::createText(std::string text, int font_size, Color color, int layer, std::unique_ptr<Rect> dst) const {
    TTF_Font* roboto = TTF_OpenFont("./assets/fonts/Roboto-Bold.ttf", font_size);

    SDL_Color sdlColor;
    sdlColor.r = color.r;
    sdlColor.g = color.g;
    sdlColor.b = color.b;
    sdlColor.a = color.a;
    SDL_Surface* surface = TTF_RenderText_Solid(roboto, text.c_str(), sdlColor);

    if (surface == nullptr) {
        std::cout << "Failed to load surface " << text
            << " error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    auto shared_texture = std::shared_ptr<SDL_Texture>(renderer.get()->createTextureFromSurface(surface), SDL_DestroyTexture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(roboto);

    return std::make_unique<Texture>(shared_texture, layer, std::move(dst));
}

std::unique_ptr<Circle> RenderableFactory::createCircle(int x, int y, int radius, bool filled, Color color, int layer) const {
    return std::make_unique<Circle>(x, y, radius, filled, color, layer);
}

std::unique_ptr<Line> RenderableFactory::createLine(int x1, int y1, int x2, int y2, Color color, int layer) const {
    return std::make_unique<Line>(x1, y1, x2, y2, color, layer);
}