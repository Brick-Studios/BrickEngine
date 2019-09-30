#include <iostream>
#include <vector>
#include <unordered_map> 
#include <cstdlib>
#include <string>
#include <typeinfo>

#include "brickengine/entities/entity_manager.hpp"

EntityManager::EntityManager(){
    entities = std::unique_ptr<std::vector<int>>(new std::vector<int>());
    lowest_unassigned_entity_id = std::unique_ptr<int>(new int(-1));
    components_by_class = std::unique_ptr<std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>>(new std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>());
}

int EntityManager::createEntity(const std::vector<Component> &components){
    entities->push_back(++*lowest_unassigned_entity_id);

    for(auto const c : components){
        addComponentToEntity(*lowest_unassigned_entity_id, c);
    }

    return *lowest_unassigned_entity_id;
}

void EntityManager::addComponentToEntity(const int entityId, const Component component){
    std::string componentType {std::string(typeid(component).name())};

    if(components_by_class->count(componentType) == 0){
        components_by_class->insert(std::make_pair(componentType, std::unordered_map<int, std::unique_ptr<Component>>()));
    }

    components_by_class->at(componentType).insert(std::make_pair(entityId, std::make_unique<Component>(component)));
}

void EntityManager::removeEntity(const int entityId){
    entities->erase(entities->begin() + entityId);
}

EntityManager::~EntityManager(){

}