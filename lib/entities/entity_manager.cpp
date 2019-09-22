#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>
#include <cstdlib>

#include "brickengine/entities/entity_manager.hpp"

EntityManager::EntityManager(){
    
    entities.push_back(std::unique_ptr<int>{new int(5)});

    for(std::unique_ptr<int>& e : entities){
        std::cout << *e << '\n';
    }

    // components_by_class["Jan"] = std::unique_ptr{new Component()};

    


}

EntityManager::~EntityManager(){
    
}