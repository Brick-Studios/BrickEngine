#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>

#include "entities/entity_manager.hpp"

EntityManager::EntityManager(){
    
    for(std::unique_ptr<int>& e : entities){
        std::cout << *e << '\n';
    }

    componentsByClass.insert(std::make_pair(std::unique_ptr<std::string>(new std::string("woeifjewfiowejf"), std::unique_ptr<Component>));
}

EntityManager::~EntityManager(){
    
}