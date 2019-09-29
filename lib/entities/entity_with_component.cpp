#include <iostream>

#include "brickengine/entities/entity_with_component.hpp"

template <class T>
EntityWithComponent::EntityWithComponent(int entityId, T component){
    entityId = std::unique_ptr<int>(entityId);
    component = std::shared_ptr<T>(component);
}

EntityWithComponent::~EntityWithComponent(){

}