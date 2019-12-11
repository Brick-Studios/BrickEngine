#ifndef FILE_ANIMATION_COMPONENT_HPP
#define FILE_ANIMATION_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"


class AnimationComponent : public ComponentImpl<AnimationComponent>{
public:
    AnimationComponent(double update_time, int sprite_size);
    static std::string getNameStatic();

    // Time passed
    double time;
    int seconds;
    // Current sprite
    int sprite;
    // How often it should swap between sprites
    double update_time;
    // How many sprites are in the spritesheet
    int sprite_size;
};

#endif // FILE_ANIMATION_COMPONENT_HPP 