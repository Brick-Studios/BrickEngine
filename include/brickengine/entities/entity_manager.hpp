#ifndef FILE_ENTITY_MANAGER_HPP
#define FILE_ENTITY_MANAGER_HPP

#include "brickengine/components/component.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map> 

class EntityManager{
    public:
        EntityManager();
        ~EntityManager();

        void createEntity(const std::vector<Component> components);
        void removeEntity();
        
        const Component getComponent(const int entityId);

        void addComponentToEntity(const int entityId, const Component component); 
        void removeComponentFromEntity(const int entityId);

    private:
        std::vector<std::unique_ptr<int>> entities;
        std::unique_ptr<int> lowest_unassigned_entity_id { new int(-1) };
        std::unordered_map<std::string, std::unique_ptr<Component>> components_by_class;
};

#endif /* FILE_ENTITY_MANAGER_HPP */