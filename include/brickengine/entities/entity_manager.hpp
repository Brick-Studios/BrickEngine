#ifndef FILE_ENTITY_MANAGER_HPP
#define FILE_ENTITY_MANAGER_HPP

#include "brickengine/components/component.hpp"
#include "brickengine/components/component_impl.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/data/position.hpp"
#include "brickengine/components/data/scale.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map> 
#include <type_traits>
#include <utility>
#include <set>

class EntityManager{
public:
    EntityManager() {
        lowest_unassigned_entity_id = -1;
        components_by_class = std::unique_ptr<std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>>(new std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>());
    };
    ~EntityManager() = default;

    int createEntity(const std::unique_ptr<std::vector<std::unique_ptr<Component>>> components, std::optional<int> parentIdOpt){
        int entityId = ++lowest_unassigned_entity_id;

        for(auto& c : *components)
            addComponentToEntity(lowest_unassigned_entity_id, std::move(c));

        if(parentIdOpt)
            setParent(entityId, parentIdOpt.value());

        return entityId;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    std::unique_ptr<std::vector<std::pair<int, T*>>> getEntitiesByComponent(){
        std::string componentType = T::getNameStatic();
        if (components_by_class->count(componentType) < 1)
            return std::make_unique<std::vector<std::pair<int, T*>>>();
        auto list = std::make_unique<std::vector<std::pair<int, T*>>>(components_by_class->at(componentType).size());
        list->clear();
        if(components_by_class->count(componentType) > 0){
            for(auto const& [entityId, component] : components_by_class->at(componentType)){
                list->push_back(std::make_pair(entityId, dynamic_cast<T*>(component.get())));
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
        if(components_by_class->count(componentType) > 0) {
            if (components_by_class->at(componentType).count(entityId) > 0)
                return (T*) components_by_class->at(componentType).at(entityId).get();
        }
        return (T*) nullptr;
    }

    void addComponentToEntity(const int entityId, std::unique_ptr<Component> component){
        std::string componentType = component.get()->getName();

        if(components_by_class->count(componentType) == 0)
            components_by_class->insert(std::make_pair(componentType, std::unordered_map<int, std::unique_ptr<Component>>()));

        components_by_class->at(componentType).insert(std::make_pair(entityId, std::move(component)));
    }

    void removeEntity(const int entityId) {
        for(auto& component : *components_by_class)
            component.second.erase(entityId);
    }

    void setParent(int childId, int parentId) {
        if (family_hierarcy_parents.count(childId)) {
            int oldParent { family_hierarcy_parents[childId] };
            family_hierarcy_children[oldParent].erase(childId);
        }

        family_hierarcy_parents.insert_or_assign(childId, parentId);
        if (!family_hierarcy_children.count(parentId)) {
            family_hierarcy_children[parentId].insert(childId);
        }
        else {
            family_hierarcy_children.insert({parentId, std::set<int>()});
            family_hierarcy_children[parentId].insert(childId);
        }
    }

    std::optional<int> getParent(int entityId) {
        if (!family_hierarcy_parents.count(entityId))
            return std::nullopt;
        else
            return family_hierarcy_parents[entityId];
    }

    std::set<int> getChildren(int entityId) {
        if (!family_hierarcy_children.count(entityId))
            return std::set<int>();
        else
            return family_hierarcy_children[entityId];
    }

    void moveOutOfParentsHouse(int entityId) {
        if (!family_hierarcy_parents.count(entityId)) return;

        int oldParent { family_hierarcy_parents[entityId] };
        family_hierarcy_children[oldParent].erase(entityId);
        family_hierarcy_parents.erase(entityId);
    }

    std::pair<Position, Scale> getAbsoluteTransform(int entityId){
        auto transform = getComponent<TransformComponent>(entityId);
        auto position = Position(transform->xPos, transform->yPos);
        auto scale = Scale(transform->xScale, transform->yScale);
        if (auto parent = getParent(entityId)) {
            auto [ parent_position, parent_scale ] = getAbsoluteTransform(*parent);

            position.x += parent_position.x;
            position.y += parent_position.y;
            scale.x *= parent_scale.x;
            scale.y *= parent_scale.y;
        }

        return std::make_pair(position, scale);
    }
private:
    int lowest_unassigned_entity_id;
    std::unique_ptr<std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>>> components_by_class;
    std::unordered_map<int, int> family_hierarcy_parents;
    std::unordered_map<int, std::set<int>> family_hierarcy_children;
};

#endif // FILE_ENTITY_MANAGER_HPP
