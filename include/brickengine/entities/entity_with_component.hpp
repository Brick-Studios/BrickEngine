#ifndef FILE_ENTITY_WITH_COMPONENT_HPP
#define FILE_ENTITY_WITH_COMPONENT_HPP

#include "brickengine/components/component.hpp"
#include <iostream>

template <class T>
class EntityWithComponent{
public:
    EntityWithComponent(int entityId, T* component) : id(entityId), component(component) {
    }
    ~EntityWithComponent() {
    }

    int id;
    T* component;
};

#endif /* FILE_ENTITY_WITH_COMPONENT_HPP */