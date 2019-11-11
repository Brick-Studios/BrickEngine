#include "brickengine/components/renderables/texture_component.hpp"

TextureComponent::TextureComponent(std::unique_ptr<Texture> t) : texture(std::move(t)) {}

std::string TextureComponent::getNameStatic() {
    return "TextureComponent";
}

Texture* TextureComponent::getTexture() const {
    return this->texture.get();
}