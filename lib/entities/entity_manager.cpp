#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>
#include <cstdlib>
#include <typeinfo>

#include "brickengine/entities/entity_manager.hpp"

EntityManager::EntityManager(){
    
    // entities.push_back(std::unique_ptr<int>{new int(5)});

    // for(std::unique_ptr<int>& e : entities){
    //     std::cout << *e << '\n';
    // }

    // components_by_class["Jan"] = std::unique_ptr<Component>{new Component()};

    // for(auto const& map: components_by_class){
    //     std::cout << "key: " + map.first << ", " << map.second << "\n";
    // }

    addComponentToEntity(1, Component());
}

int EntityManager::createEntity(const std::vector<Component> &components){
    entities.push_back(std::unique_ptr<int>{new int(++*lowest_unassigned_entity_id)});

    for(auto const c : components){
        addComponentToEntity(*lowest_unassigned_entity_id, c);
    }

    return *lowest_unassigned_entity_id;
}

void EntityManager::addComponentToEntity(const int entityId, const Component component){
    std::unique_ptr<std::string> componentType {new std::string(typeid(component).name())};

    std::cout << "entityId is: " << typeid(int).name() << '\n';
    std::cout << "component is: " << typeid(component).name() << '\n';
}

EntityManager::~EntityManager(){
    
}