#ifndef FILE_ENTITY_MANAGER_HPP
#define FILE_ENTITY_MANAGER_HPP

#include "brickengine/components/component.hpp"
#include "brickengine/entities/entity_with_component.hpp"

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

        template <class T>
        std::unique_ptr<std::vector<std::unique_ptr<EntityWithComponent<T>>>> getAllEntities(){
            std::string componentType {std::string(typeid(T).name())};
            auto list = std::unique_ptr<std::vector<std::unique_ptr<EntityWithComponent<T>>>>(new std::vector<std::unique_ptr<EntityWithComponent<T>>>(components_by_class->at(componentType).size()));
            list.get()->clear();
            if(components_by_class->count(componentType) > 0){
                for(auto const& obj : components_by_class->at(componentType)){
                    std::unique_ptr<EntityWithComponent<T>> ewc (new EntityWithComponent<T>(obj.first, obj.second.get()));
                    list.get()->push_back(std::move(ewc));
                }
            }
            return list;
        }
        
        template <class T>
        void removeComponentFromEntity(const int entityId){    
            std::string componentType {std::string(typeid(T).name())};

            components_by_class->at(componentType).erase(entityId);
        }

        template <class T>
        T* getComponent(const int entityId) const{
            std::string componentType {std::string(typeid(T).name())};
            if(components_by_class->count(componentType) > 0){
                return (T*) components_by_class->at(componentType).at(entityId).get();
            }else{
                return (T*) nullptr;
            }
        }

        void addComponentToEntity(const int entityId, const Component component); 

    private:
        std::unique_ptr<std::vector<int>> entities;
        std::unique_ptr<int> lowest_unassigned_entity_id;
        std::unique_ptr<std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>> components_by_class;
};

#endif /* FILE_ENTITY_MANAGER_HPP */