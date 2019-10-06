#ifndef FILE_HEALTH_COMPONENT_HPP
#define FILE_HEALTH_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class HealthComponent : public ComponentImpl<HealthComponent> {
public:
    HealthComponent(int hp): hp(hp) { };
    HealthComponent(): hp(0) { };
    int hp;
    static std::string getNameStatic() {
        return "HealthComponent";
    };
};

#endif /* FILE_HEALTH_COMPONENT_HPP */