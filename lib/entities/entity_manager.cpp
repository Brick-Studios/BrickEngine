#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>
#include <cstdlib>
#include <typeinfo>

#include "brickengine/entities/entity_manager.hpp"

EntityManager::EntityManager(){
    
    entities = std::unique_ptr<std::vector<int>>(new std::vector<int>());
    components_by_class = std::unique_ptr<std::unordered_map<std::string, std::vector<std::unique_ptr<Component>>>>(new std::unordered_map<std::string, std::vector<std::unique_ptr<Component>>>());
    
    std::vector<Component> componentList;

    componentList.push_back(Component());

    createEntity(componentList);

    printEntities();

    //std::cout << "Component: " << typeid(getComponent(0, Component())).name() << "\n";

    // removeComponentFromEntity(0, Component());
    
    //std::cout << "Component: " << typeid(getComponent(0, Component())).name() << "\n";
}

int EntityManager::createEntity(const std::vector<Component> &components){
    entities->push_back(++*lowest_unassigned_entity_id);

    for(auto const c : components){
        addComponentToEntity(*lowest_unassigned_entity_id, c);
    }

    return *lowest_unassigned_entity_id;
}

void EntityManager::addComponentToEntity(const int entityId, Component component){
    std::string componentType {std::string(typeid(component).name())};

    if(components_by_class->count(componentType) == 0){
        components_by_class->insert(std::make_pair(componentType, std::vector<std::unique_ptr<Component>>()));
    }

    components_by_class->at(componentType).insert(components_by_class->at(componentType).begin() + entityId,std::make_unique<Component>(component));
}

template <class T>
void EntityManager::removeComponentFromEntity(const int entityId, const T type){    
    std::string componentType {std::string(typeid(type).name())};

    std::cout << entityId << "entity Id" << std::endl;
    components_by_class->at(componentType).erase(components_by_class->at(componentType).begin() + entityId);
}

template <class T>
const T* EntityManager::getComponent(const int entityId, const T type){
    std::string componentType {std::string(typeid(type).name())};
    if(components_by_class->count(componentType) > 0){
        return (T)components_by_class->at(componentType).at(entityId).get();
    }
    else
    {
        return nullptr;
    }
}

void EntityManager::removeEntity(const int entityId){
    entities->erase(entities->begin() + entityId);
}

void EntityManager::printEntities(){
    for(const int& e : *entities){
        std::cout << e << '\n';
    }
}

EntityManager::~EntityManager(){

}