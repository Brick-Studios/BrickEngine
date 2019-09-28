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

        int createEntity(const std::vector<Component> &components);
        void removeEntity(const int entityId);
        
        const Component getComponent(const int entityId);

        void addComponentToEntity(const int entityId, const Component component); 
        void removeComponentFromEntity(const int entityId);

        void printEntities();

    private:
        std::unique_ptr<std::vector<int>> entities;
        std::unique_ptr<int> lowest_unassigned_entity_id { new int(-1) };
        std::unique_ptr<std::unordered_map<std::string, std::vector<Component>>> components_by_class;
};

#endif /* FILE_ENTITY_MANAGER_HPP */