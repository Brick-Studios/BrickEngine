#include <memory>
#include <string>
#include <iostream>
#include "SDL2/SDL_ttf.h"

#include "brickengine/rendering/renderable_factory.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/texture.hpp"
#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderables/data/rect.hpp"

RenderableFactory::RenderableFactory(std::shared_ptr<Renderer> r) : renderer(r) {
}

std::unique_ptr<Texture> RenderableFactory::createImage(std::string path, int layer, std::unique_ptr<Rect> dst) const {
    SDL_Texture* texture = this->createBMPTexture(path);

    return std::make_unique<Texture>(texture, layer, std::move(dst));
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

    SDL_Texture* texture = renderer.get()->createTextureFromSurface(surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(roboto);

    return std::make_unique<Texture>(texture, layer, std::move(dst));
}

std::unique_ptr<Circle> RenderableFactory::createCircle(int x, int y, int radius, bool filled, Color color, int layer) const {
    return std::make_unique<Circle>(x, y, radius, filled, color, layer);
}

std::unique_ptr<Line> RenderableFactory::createLine(int x1, int y1, int x2, int y2, Color color, int layer) const {
    return std::make_unique<Line>(x1, y1, x2, y2, color, layer);
}

SDL_Texture* RenderableFactory::createBMPTexture(std::string path) const {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());

    if (surface == nullptr) {
        std::cout << "Failed to load surface " << path
            << " error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* t = renderer.get()->createTextureFromSurface(surface);
    SDL_FreeSurface(surface);
    return t;
}