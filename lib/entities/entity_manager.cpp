#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>
#include <cstdlib>
#include <typeinfo>

#include "brickengine/entities/entity_manager.hpp"

EntityManager::EntityManager(){
    


    // for(auto const& map: components_by_class){
    //     std::cout << "key: " + map.first << ", " << map.second << "\n";
    // }
    
    // std::unique_ptr<std::vector<Component>> componentList;
    // componentList->push_back(new Component());
    // createEntity(componentList);

    //addComponentToEntity(1, Component());
    
    printEntities();
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
        components_by_class->insert(std::make_pair(componentType, std::vector<Component>()));
    }
    
    std::vector<Component> componentsPerId = components_by_class->at(componentType);
    componentsPerId[entityId] = component;
}

void EntityManager::removeComponentFromEntity(const int entityId){
    
}

const Component EntityManager::getComponent(const int entityId){
    
}

void EntityManager::removeEntity(const int entityId){
    entities->erase(entities->begin() + entityId);
}

void EntityManager::printEntities(){
    for(std::unique_ptr<int>& e : entities){
        std::cout << *e << '\n';
    }
}

EntityManager::~EntityManager(){

}