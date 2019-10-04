#ifndef FILE_TEXTURE_HPP
#define FILE_TEXTURE_HPP

#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/data/rect.hpp"

class Renderer;

class Texture : public Renderable {
public:
    Texture(SDL_Texture* texture, int layer, std::unique_ptr<Rect> dst);
    Texture(SDL_Texture* texture, int layer, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src);
    void render(Renderer& r);
    virtual Rect* getSrcRect();
    virtual Rect* getDstRect();
    virtual SDL_Texture* getTexture();
protected:
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture;
    std::unique_ptr<Rect> src;
    std::unique_ptr<Rect> dst;
};

#endif // FILE_TEXTURE_HPP