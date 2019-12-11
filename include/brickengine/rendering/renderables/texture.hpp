#ifndef FILE_TEXTURE_HPP
#define FILE_TEXTURE_HPP

#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/data/rect.hpp"

class Renderer;

class Texture : public Renderable {
public:
    Texture(std::shared_ptr<SDL_Texture> texture, int layer, std::unique_ptr<Rect> dst);
    Texture(std::shared_ptr<SDL_Texture> texture, int layer, int alpha, std::unique_ptr<Rect> dst);
    Texture(std::shared_ptr<SDL_Texture> texture, int layer, int alpha, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src);
    Texture(const Texture& other);
    Texture(Texture&& other) noexcept = delete;
    Texture& operator=(Texture&& other) = delete;
    Texture& operator=(const Texture& other) = delete;
    // This can stay default because we don't own any pointers here
    ~Texture() = default;
    void render(Renderer& r);
    virtual Rect* getSrcRect() const;
    virtual Rect* getDstRect() const;
    virtual SDL_Texture* getTexture() const;
    SDL_RendererFlip getFlip() const;
    void setFlip(SDL_RendererFlip flip);
protected:
    std::shared_ptr<SDL_Texture> texture;
    std::unique_ptr<Rect> src;
    std::unique_ptr<Rect> dst;
    SDL_RendererFlip flip;
};

#endif // FILE_TEXTURE_HPP