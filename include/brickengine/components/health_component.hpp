#ifndef FILE_HEALTH_COMPONENT_HPP
#define FILE_HEALTH_COMPONENT_HPP

#include "component.hpp"

class HealthComponent : public Component {
public:
    HealthComponent(int hp): hp(hp) { };
    HealthComponent(): hp(0) { };
    int hp;
    std::string getName() {
        return "HealthComponent";
    };
};

#endif /* FILE_HEALTH_COMPONENT_HPP */