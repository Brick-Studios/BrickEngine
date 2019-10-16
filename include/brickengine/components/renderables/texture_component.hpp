#ifndef FILE_TEXTURE_COMPONENT_HPP
#define FILE_TEXTURE_COMPONENT_HPP

#include <memory>
#include "brickengine/components/component_impl.hpp"
#include "brickengine/rendering/renderables/texture.hpp"


class TextureComponent : public ComponentImpl<TextureComponent>{
public:
    TextureComponent(std::unique_ptr<Texture> t);
    static std::string getNameStatic();

    Texture* getTexture() const;
private:
    std::unique_ptr<Texture> texture;
};

#endif // FILE_TEXTURE_COMPONENT_HPP