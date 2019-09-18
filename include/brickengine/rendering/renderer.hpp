#ifndef FILE_RENDERER_HPP
#define FILE_RENDERER_HPP

#include <functional>

#include "rendering/renderables/image.hpp"

class Renderer {
public:
    void ClearScreen();
    void DrawScreen();
    void Render(Renderable renderable);
    void Render(Image renderable);
    void Render();
};

#endif 