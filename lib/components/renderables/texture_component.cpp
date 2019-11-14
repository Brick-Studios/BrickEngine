#include "brickengine/components/renderables/texture_component.hpp"

TextureComponent::TextureComponent(std::unique_ptr<Texture> t) : texture(std::move(t)) {}

TextureComponent::TextureComponent(const TextureComponent& other) {
    this->texture = std::make_unique<Texture>(*other.texture);
}
TextureComponent& TextureComponent::operator=(const TextureComponent& other) {
    if (this != &other) {
        this->texture = std::make_unique<Texture>(*other.texture);
    }
    return *this;
}

std::string TextureComponent::getNameStatic() {
    return "TextureComponent";
}

Texture* TextureComponent::getTexture() const {
    return this->texture.get();
}