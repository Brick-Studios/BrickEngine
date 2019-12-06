#ifndef FILE_ENTITY_COMPONENTS_HPP
#define FILE_ENTITY_COMPONENTS_HPP

#include <string>
#include <memory> 
#include <optional>
#include <vector> 

#include "brickengine/components/component.hpp"

// This struct is used for entities that are uninitialized.
struct EntityComponents {
    std::unique_ptr<std::vector<std::unique_ptr<Component>>> components;
    std::vector<std::string> tags;
}; 

#endif // FILE_ENTITY_COMPONENTS_HPP