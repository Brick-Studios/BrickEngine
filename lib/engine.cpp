#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>

#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderable_factory.hpp"

#include "SDL2_gfxPrimitives.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

BrickEngine::BrickEngine(const std::string window_name, const int window_width, const int window_height, std::vector<int> layers, int fps_cap) : fps_cap(fps_cap), window(nullptr, nullptr) {
    this->fps = 5;
    this->layers = layers;
    this->top_layer = layers.back();
    this->window_name = window_name;
    this->window_height = window_height;
    this->window_width = window_width;
}

void BrickEngine::start() {
    //Initialize SDL
    if(SDL_Init( SDL_INIT_VIDEO ) != 0)
    {
        std::cout << "SDL failed to init! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
     //Initialize SDL_ttf
    if(TTF_Init() == -1 )
    {
        std::cout << "SDL_ttf failed to init! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
     //Initialize SDL_image
    // load support for the JPG and PNG image formats
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int img_initted_flags = IMG_Init(img_flags);
    if((img_initted_flags&img_flags) != img_flags) {
        std::cout << "SDL_image failed to init with JPG and PNG support! SDL_Error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    SDL_Window* window_ptr(SDL_CreateWindow(
      this->window_name.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      this->window_width,
      this->window_height,
      0
    ));
    if(!window_ptr)
    {
        std::cout << "SDL window failed to open! SDL_Error: " << IMG_GetError() << std::endl;
        exit(1);
    }
    this->window = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>(window_ptr, SDL_DestroyWindow);
    SDL_Renderer* renderer_ptr(SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED));
    if(!renderer_ptr)
    {
        std::cout << "SDL renderer failed to open! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer_unique_ptr(renderer_ptr, SDL_DestroyRenderer);
    this->renderer = std::shared_ptr<Renderer>(new Renderer(std::move(renderer_unique_ptr), layers));

    this->resource_manager = std::make_shared<ResourceManager>(renderer);
    this->renderableFactory = std::unique_ptr<RenderableFactory>(new RenderableFactory(renderer, resource_manager));

    std::cout << "Window openend finished" << std::endl;
}

void BrickEngine::stop() {
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

void BrickEngine::delay(std::chrono::time_point<std::chrono::high_resolution_clock> start_time,
                          std::chrono::time_point<std::chrono::high_resolution_clock> end_time) {
    using nanoseconds = std::chrono::nanoseconds;
    using seconds = std::chrono::duration<double>;

    nanoseconds delta_time_in_nanoseconds = std::chrono::duration_cast<nanoseconds>(end_time - start_time);

    nanoseconds fps_frame_time { (1'000'000'000 / fps_cap)};
    nanoseconds delay { 0 };
    if(delta_time_in_nanoseconds < fps_frame_time) {
        delay = (fps_frame_time - delta_time_in_nanoseconds);
        std::this_thread::sleep_for(delay);
    }
    this->delta_time = std::chrono::duration_cast<seconds>(delta_time_in_nanoseconds + delay).count();
    this->fps = 1.0 / delta_time;
}

void BrickEngine::drawFpsCounter() {
    auto dst = std::unique_ptr<Rect>(new Rect { 0, 0, 75, 75});
    this->fps_counter = this->getRenderableFactory()->createText(std::to_string(this->fps), 24, { 255, 255, 255, 0}, this->top_layer, std::move(dst));
    this->getRenderer()->queueRenderable(fps_counter.get());
}

int BrickEngine::getFps() const {
    return this->fps;
}

double BrickEngine::getDeltatime() const {
    return this->delta_time;
}

RenderableFactory* BrickEngine::getRenderableFactory() const {
    return this->renderableFactory.get();
}

Renderer* BrickEngine::getRenderer() const {
    return this->renderer.get();
}

BrickEngine::EngineTick BrickEngine::getTicks() const {
    return std::chrono::high_resolution_clock::now();
}

int BrickEngine::getWindowWidth() const {
    return this->window_width;
}

int BrickEngine::getWindowHeight() const {
    return this->window_height;
}