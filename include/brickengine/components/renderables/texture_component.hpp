#ifndef FILE_TEXTURE_COMPONENT_HPP
#define FILE_TEXTURE_COMPONENT_HPP

#include <memory>
#include "brickengine/components/component_impl.hpp"
#include "brickengine/rendering/renderables/texture.hpp"


class TextureComponent : public ComponentImpl<TextureComponent>{
public:
    TextureComponent(std::unique_ptr<Texture> t);
    TextureComponent(const TextureComponent& other);
    TextureComponent(TextureComponent&& other) noexcept = default;
    TextureComponent& operator=(TextureComponent&& other) = default;
    TextureComponent& operator=(const TextureComponent& other);
    // This can stay default because we don't own any pointers here
    ~TextureComponent() = default;
    static std::string getNameStatic();

    Texture* getTexture() const;
private:
    std::unique_ptr<Texture> texture;
};

#endif // FILE_TEXTURE_COMPONENT_HPP