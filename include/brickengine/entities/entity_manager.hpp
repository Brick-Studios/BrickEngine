#ifndef FILE_ENTITY_MANAGER_HPP
#define FILE_ENTITY_MANAGER_HPP

#include "brickengine/components/component.hpp"
#include "brickengine/components/component_impl.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/data/position.hpp"
#include "brickengine/components/data/scale.hpp"
#include "brickengine/entities/exceptions/grandparents_not_supported.hpp"

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

    // the int in the optional pair is the parent id
    // the bool in the optional pair is whether the transform is already relative
    int createEntity(const std::unique_ptr<std::vector<std::unique_ptr<Component>>> components, std::optional<std::pair<int,bool>> parentOpt){
        int entity_id = ++lowest_unassigned_entity_id;

        for(auto& c : *components)
            addComponentToEntity(lowest_unassigned_entity_id, std::move(c));

        if(parentOpt)
            setParent(entity_id, parentOpt.value().first, parentOpt.value().second);

        return entity_id;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    std::unique_ptr<std::vector<std::pair<int, T*>>> getEntitiesByComponent(){
        std::string component_type = T::getNameStatic();
        if (components_by_class->count(component_type) < 1)
            return std::make_unique<std::vector<std::pair<int, T*>>>();
        auto list = std::make_unique<std::vector<std::pair<int, T*>>>(components_by_class->at(component_type).size());
        list->clear();
        if(components_by_class->count(component_type) > 0){
            for(auto const& [entityId, component] : components_by_class->at(component_type)){
                list->push_back(std::make_pair(entityId, dynamic_cast<T*>(component.get())));
            }
        }
        return list;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    void removeComponentFromEntity(const int entity_id){
        std::string componentType = T::getNameStatic();

        components_by_class->at(componentType).erase(entity_id);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    T* getComponent(const int entity_id) const {
        std::string componentType = T::getNameStatic();
        if(components_by_class->count(componentType) > 0) {
            if (components_by_class->at(componentType).count(entity_id) > 0)
                return (T*) components_by_class->at(componentType).at(entity_id).get();
        }
        return (T*) nullptr;
    }

    void addComponentToEntity(const int entity_id, std::unique_ptr<Component> component){
        std::string componentType = component.get()->getName();

        if(components_by_class->count(componentType) == 0)
            components_by_class->insert({ componentType, std::unordered_map<int, std::unique_ptr<Component>>() });

        components_by_class->at(componentType).insert_or_assign(entity_id, std::move(component));
    }

    void removeEntity(const int entity_id) {
        for(auto& component : *components_by_class)
            component.second.erase(entity_id);
    }

    void setParent(int child_id, int parent_id, bool transform_is_relative) {
        if (getParent(parent_id))
            throw GrandparentsNotSupportedException();

        auto child_transform = getComponent<TransformComponent>(child_id);
        auto child_physics = getComponent<PhysicsComponent>(child_id);

        if (!transform_is_relative) {
            auto [ parent_absolute_position, parent_absolute_scale ] = getAbsoluteTransform(parent_id);
            child_transform->xPos -= parent_absolute_position.x;
            child_transform->yPos -= parent_absolute_position.y;
            child_transform->xScale /= parent_absolute_scale.x;
            child_transform->yScale /= parent_absolute_scale.y;
        }
        
        if (child_physics && child_physics->kinematic == Kinematic::IS_NOT_KINEMATIC)
            child_physics->kinematic = Kinematic::WAS_NOT_KINEMATIC;

        if (family_hierarcy_parents.count(child_id)) {
            int oldParent { family_hierarcy_parents[child_id] };
            family_hierarcy_children[oldParent].erase(child_id);
        }

        family_hierarcy_parents.insert_or_assign(child_id, parent_id);
        if (!family_hierarcy_children.count(parent_id)) {
            family_hierarcy_children[parent_id].insert(child_id);
        }
        else {
            family_hierarcy_children.insert({parent_id, std::set<int>()});
            family_hierarcy_children[parent_id].insert(child_id);
        }
    }

    std::optional<int> getParent(int id) {
        if (!family_hierarcy_parents.count(id))
            return std::nullopt;
        else
            return family_hierarcy_parents[id];
    }

    std::set<int> getChildren(int id) {
        if (!family_hierarcy_children.count(id))
            return std::set<int>();
        else
            return family_hierarcy_children[id];
    }

    void moveOutOfParentsHouse(int entity_id) {
        if (!family_hierarcy_parents.count(entity_id)) return;
        int old_parent { family_hierarcy_parents[entity_id] };
        auto old_parent_transform = getComponent<TransformComponent>(old_parent);

        auto child_transform = getComponent<TransformComponent>(entity_id);
        child_transform->xPos += old_parent_transform->xPos;
        child_transform->yPos += old_parent_transform->yPos;
        child_transform->xScale *= old_parent_transform->xScale;
        child_transform->yScale *= old_parent_transform->yScale;

        auto physics = getComponent<PhysicsComponent>(entity_id);
        if (physics && physics->kinematic == Kinematic::WAS_NOT_KINEMATIC)
            physics->kinematic = Kinematic::IS_NOT_KINEMATIC;

        family_hierarcy_children[old_parent].erase(entity_id);
        family_hierarcy_parents.erase(entity_id);
    }

    std::pair<Position, Scale> getAbsoluteTransform(int id){
        auto transform = getComponent<TransformComponent>(id);
        auto position = Position(transform->xPos, transform->yPos);
        auto scale = Scale(transform->xScale, transform->yScale);
        if (auto parent = getParent(id)) {
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
