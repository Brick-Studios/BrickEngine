#ifndef FILE_BRICKENGINE_HPP
#define FILE_BRICKENGINE_HPP

#include <optional>
#include <iostream>
#include <string>
#include <memory>
#include <string>
#include <chrono>

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderable_factory.hpp"
#include "brickengine/resource_manager.hpp"
#include "brickengine/sound/sound_manager.hpp"

class BrickEngine {
public:
    using EngineTick = std::chrono::time_point<std::chrono::high_resolution_clock>;
    // You need to supply all the used layers to this constructors, layers that the engine doesn't know of will not get drawn!
    BrickEngine(const std::string window_name, const int window_width, const int window_height, std::vector<int> layers, int fps_cap, std::string font_path);
    ~BrickEngine() = default;
    void start();
    void stop();
    void delay(EngineTick start_time,
                EngineTick end_time);
    void drawFpsCounter();
    RenderableFactory* getRenderableFactory() const;
    Renderer* getRenderer() const;
    SoundManager& getSoundManager() const;
    int getFps() const;
    double getDeltatime() const;
    EngineTick getTicks() const;
    int getWindowWidth() const;
    int getWindowHeight() const;
    void toggleCursor(bool value) const;
private:
    std::vector<int> layers;
    int top_layer;
    int fps;
    int fps_cap;
    double delta_time;
    std::string window_name;
    int window_height;
    int window_width;
    std::string font_path;
    std::unique_ptr<Renderable> fps_counter;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
    std::unique_ptr<RenderableFactory> renderableFactory;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<ResourceManager> resource_manager;
    std::unique_ptr<SoundManager> sound_manager;
};

#endif // FILE_BRICKENGINE_HPP
