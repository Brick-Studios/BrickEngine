#ifndef FILE_ENTITY_MANAGER_HPP
#define FILE_ENTITY_MANAGER_HPP

#include "brickengine/components/component.hpp"
#include "brickengine/components/component_impl.hpp"
#include "brickengine/entities/entity_with_component.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map> 
#include <type_traits>

class EntityManager{
public:
    EntityManager() {
        lowest_unassigned_entity_id = -1;
        components_by_class = std::unique_ptr<std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>>(new std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>());
    };
    ~EntityManager() = default;

    int createEntity(const std::unique_ptr<std::vector<std::unique_ptr<Component>>> components){
        int entityId = ++lowest_unassigned_entity_id;

        for(auto& c : *components)
            addComponentToEntity(lowest_unassigned_entity_id, std::move(c));

        return entityId;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    std::unique_ptr<std::vector<std::unique_ptr<EntityWithComponent<T>>>> getEntitiesByComponent(){
        std::string componentType = T::getNameStatic();
        auto list = std::unique_ptr<std::vector<std::unique_ptr<EntityWithComponent<T>>>>(new std::vector<std::unique_ptr<EntityWithComponent<T>>>(components_by_class->at(componentType).size()));
        list.get()->clear();
        if(components_by_class->count(componentType) > 0){
            for(auto const& obj : components_by_class->at(componentType)){
                std::unique_ptr<EntityWithComponent<T>> ewc (new EntityWithComponent<T>(obj.first, dynamic_cast<T*>(obj.second.get())));
                list.get()->push_back(std::move(ewc));
            }
        }
        return list;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    void removeComponentFromEntity(const int entityId){
        std::string componentType = T::getNameStatic();

        components_by_class->at(componentType).erase(entityId);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    T* getComponent(const int entityId) const {
        std::string componentType = T::getNameStatic();
        if(components_by_class->count(componentType) > 0)
            return (T*) components_by_class->at(componentType).at(entityId).get();
        else
            return (T*) nullptr;
    }

    void addComponentToEntity(const int entityId, std::unique_ptr<Component> component){
        std::string componentType = component.get()->getName();

        if(components_by_class->count(componentType) == 0)
            components_by_class->insert(std::make_pair(componentType, std::unordered_map<int, std::unique_ptr<Component>>()));

        components_by_class->at(componentType).insert(std::make_pair(entityId, std::move(component)));
    }

    void removeEntity(const int entityId){
        for(auto& component : *components_by_class)
            component.second.erase(entityId);
    }

private:
    int lowest_unassigned_entity_id;
    std::unique_ptr<std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>> components_by_class;
};

#endif /* FILE_ENTITY_MANAGER_HPP */