#ifndef FILE_ENTITY_MANAGER_HPP
#define FILE_ENTITY_MANAGER_HPP

#include "components/component.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map> 

class EntityManager{
    public:
        EntityManager();
        ~EntityManager();

        void CreateEntity(const std::vector<Component> components);
        void RemoveEntity();
        
        const Component GetComponent(const int entityId);

        void AddComponentToEntity(const int entityId, const Component component); 
        void RemoveComponentFromEntity(const int entityId);

    private:
        std::vector<std::unique_ptr<int>> entities;
        std::unique_ptr<int> lowestUnassignedEntityId { new int(-1) };
        std::unordered_map<std::unique_ptr<std::string>, std::unique_ptr<Component>> componentsByClass;
};

#endif /* FILE_ENTITY_MANAGER_HPP */