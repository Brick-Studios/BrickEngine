#include <iostream>
#include <vector>
#include <unordered_map> 
#include <string>
#include <cstdlib>

#include "entities/entity_manager.hpp"

EntityManager::EntityManager(){
    
    for(std::unique_ptr<int>& e : entities){
        std::cout << *e << '\n';
    }

    
}

EntityManager::~EntityManager(){
    
}