#ifndef FILE_ENTITY_MANAGER_HPP
#define FILE_ENTITY_MANAGER_HPP

#include "brickengine/components/component.hpp"
#include "brickengine/components/component_impl.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/data/position.hpp"
#include "brickengine/components/data/scale.hpp"
#include "brickengine/entities/exceptions/grandparents_not_supported.hpp"
#include "brickengine/entities/exceptions/entity_not_found.hpp"
#include "brickengine/entities/exceptions/component_not_found.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map> 
#include <type_traits>
#include <utility>
#include <set>
#include <functional>

class EntityManager {
public:
    EntityManager()
        : lowest_unassigned_entity_id(-1) {}
    ~EntityManager() = default;

    void setGetCurrentSceneTagFunction(std::function<std::optional<std::string>()> fn) {
        get_current_scene_tag_function = fn;
    }

    // the int in the optional pair is the parent id
    // the bool in the optional pair is whether the transform is already relative
    int createEntity(const std::unique_ptr<std::vector<std::unique_ptr<Component>>> components,
                     std::optional<std::pair<int,bool>> parentOpt = std::nullopt,
                     std::optional<std::string> scene_tag = std::nullopt) {
        int entity_id = ++lowest_unassigned_entity_id;

        for (auto& c : *components)
            addComponentToEntity(lowest_unassigned_entity_id, std::move(c));

        if (parentOpt)
            setParent(entity_id, parentOpt.value().first, parentOpt.value().second);

        if (get_current_scene_tag_function && !scene_tag) {
            if (auto current_scene_tag = (*get_current_scene_tag_function)()) {
                setTag(entity_id, *current_scene_tag);
            }
        } else if (scene_tag) {
            setTag(entity_id, *scene_tag);
        }

        return entity_id;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    std::vector<std::pair<int, T*>> getEntitiesByComponent() {
        std::string component_type = T::getNameStatic();
        if (components_by_class.count(component_type) < 1)
            return std::vector<std::pair<int, T*>>();
        std::vector<std::pair<int, T*>> list { components_by_class.at(component_type).size() };
        list.clear();
        if(components_by_class.count(component_type) > 0){
            for(auto const& [entity_id, component] : components_by_class.at(component_type)){
                list.push_back(std::make_pair(entity_id, dynamic_cast<T*>(component.get())));
            }
        }
        return list;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    void removeComponentFromEntity(const int entity_id){
        std::string component_type = T::getNameStatic();

        components_by_class.at(component_type).erase(entity_id);
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    T* getComponent(const int entity_id) const {
        std::string component_type = T::getNameStatic();
        if(components_by_class.count(component_type) > 0) {
            if (components_by_class.at(component_type).count(entity_id) > 0)
                return (T*) components_by_class.at(component_type).at(entity_id).get();
        }
        return (T*) nullptr;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    std::vector<std::pair<int, T*>> getChildrenWithComponent(const int parent_id) const {
        std::vector<std::pair<int, T*>> results;

        if (!family_hierarchy_children.count(parent_id))
            return results;

        std::string component_type = T::getNameStatic();
        for (auto child_id : family_hierarchy_children.at(parent_id)) {
            if (components_by_class.count(component_type)) {
                if (components_by_class.at(component_type).count(child_id))
                    results.push_back(std::make_pair(
                        child_id, 
                        static_cast<T*>(components_by_class.at(component_type).at(child_id).get())));
            }
        }
        return results;
    }

    void addComponentToEntity(const int entity_id, std::unique_ptr<Component> component){
        std::string component_type = component.get()->getName();

        if(components_by_class.count(component_type) == 0)
            components_by_class.insert({ component_type, std::unordered_map<int, std::unique_ptr<Component>>() });

        components_by_class.at(component_type).insert_or_assign(entity_id, std::move(component));
    }

    void removeEntity(const int entity_id) {
        auto children = getChildren(entity_id);
        // If this entity has children
        if (!children.empty()) {
            // Forget that you have children
            for (auto& child_id : children) {
                family_hierarchy_parents.erase(child_id);
            }
            // Disown children
            family_hierarchy_children.erase(entity_id);
        }

        // Move out of a parents house(if it has one)
        moveOutOfParentsHouse(entity_id);

        // Remove all those tags
        if(tagging_entities.count(entity_id)) {
            std::set<std::string> tags_to_delete = tagging_entities.at(entity_id);
            for (auto& tag : tags_to_delete) {
                tagging_tags.at(tag).erase(entity_id);
                tagging_entities.at(entity_id).erase(tag);
            }
        }

        for(auto& component : components_by_class) {
            component.second.erase(entity_id);
        }
    }

    void setParent(int child_id, int parent_id, bool transform_is_relative) {
        if (getParent(parent_id))
            throw GrandparentsNotSupportedException();

        auto child_transform = getComponent<TransformComponent>(child_id);
        auto child_physics = getComponent<PhysicsComponent>(child_id);

        if (!transform_is_relative) {
            auto [ parent_absolute_position, parent_absolute_scale ] = getAbsoluteTransform(parent_id);
            child_transform->x_pos -= parent_absolute_position.x;
            child_transform->y_pos -= parent_absolute_position.y;
            child_transform->x_scale /= parent_absolute_scale.x;
            child_transform->y_scale /= parent_absolute_scale.y;
        }
        
        if (child_physics && child_physics->kinematic == Kinematic::IS_NOT_KINEMATIC)
            child_physics->kinematic = Kinematic::WAS_NOT_KINEMATIC;

        if (family_hierarchy_parents.count(child_id)) {
            int oldParent { family_hierarchy_parents[child_id] };
            family_hierarchy_children[oldParent].erase(child_id);
        }

        family_hierarchy_parents.insert_or_assign(child_id, parent_id);
        if (!family_hierarchy_children.count(parent_id)) {
            family_hierarchy_children[parent_id].insert(child_id);
        }
        else {
            family_hierarchy_children.insert({parent_id, std::set<int>()});
            family_hierarchy_children[parent_id].insert(child_id);
        }
    }

    std::optional<int> getParent(int id) {
        if (!family_hierarchy_parents.count(id))
            return std::nullopt;
        else
            return family_hierarchy_parents[id];
    }

    std::set<int> getChildren(int id) {
        if (!family_hierarchy_children.count(id))
            return std::set<int>();
        else
            return family_hierarchy_children[id];
    }

    void moveOutOfParentsHouse(int entity_id) {
        if (!family_hierarchy_parents.count(entity_id)) return;
        int old_parent { family_hierarchy_parents[entity_id] };
        auto old_parent_transform = getComponent<TransformComponent>(old_parent);

        auto child_transform = getComponent<TransformComponent>(entity_id);
        child_transform->x_pos += old_parent_transform->x_pos;
        child_transform->y_pos += old_parent_transform->y_pos;
        child_transform->x_scale *= old_parent_transform->x_scale;
        child_transform->y_scale *= old_parent_transform->y_scale;

        auto physics = getComponent<PhysicsComponent>(entity_id);
        if (physics && physics->kinematic == Kinematic::WAS_NOT_KINEMATIC)
            physics->kinematic = Kinematic::IS_NOT_KINEMATIC;

        family_hierarchy_children[old_parent].erase(entity_id);
        family_hierarchy_parents.erase(entity_id);
    }

    std::pair<Position, Scale> getAbsoluteTransform(int id){
        auto transform = getComponent<TransformComponent>(id);
        auto position = Position(transform->x_pos, transform->y_pos);
        auto scale = Scale(transform->x_scale, transform->y_scale);
        if (auto parent = getParent(id)) {
            auto [ parent_position, parent_scale ] = getAbsoluteTransform(*parent);

            position.x += parent_position.x;
            position.y += parent_position.y;
            scale.x *= parent_scale.x;
            scale.y *= parent_scale.y;
        }

        return std::make_pair(position, scale);
    }

    std::optional<std::set<std::string>> getTags(int entity) {
        if (tagging_entities.count(entity))
            return tagging_entities.at(entity);
        else
            return std::nullopt;
    }
    void setTag(int entity, std::string tag) {
        if (!tagging_entities.count(entity))
            tagging_entities.insert({ entity, std::set<std::string>() });
        tagging_entities.at(entity).insert(tag);
        if (!tagging_tags.count(tag))
            tagging_tags.insert({ tag, std::set<int>() });
        tagging_tags.at(tag).insert(entity);
    }
    void removeTag(int entity, std::string tag) {
        if (!tagging_entities.count(entity)) return;
        tagging_entities.at(entity).erase(tag);
        tagging_tags.at(tag).erase(entity);
    }
    std::set<int> getEntitiesWithTag(std::string tag) {
        if (!tagging_tags.count(tag))
            return std::set<int>();
        return tagging_tags.at(tag);
    }
    void removeEntitiesWithTag(std::string tag) {
        if (!tagging_tags.count(tag)) return;
        
        std::set<int> entities_to_delete = tagging_tags.at(tag);
        for (auto& entity : entities_to_delete)
            removeEntity(entity);
    }
    bool hasTag(int entity, std::string tag) {
        if (!tagging_tags.count(tag)) return false;
        return tagging_tags.at(tag).count(entity) > 0;
    }
private:
    int lowest_unassigned_entity_id;
    std::optional<std::function<std::optional<std::string>()>> get_current_scene_tag_function;
    std::unordered_map<std::string, std::unordered_map<int, std::unique_ptr<Component>>> components_by_class;
    // Families, Parent-child
    std::unordered_map<int, int> family_hierarchy_parents;
    std::unordered_map<int, std::set<int>> family_hierarchy_children;
    // Tagging, tags
    std::unordered_map<int, std::set<std::string>> tagging_entities;
    std::unordered_map<std::string, std::set<int>> tagging_tags;
};

#endif // FILE_ENTITY_MANAGER_HPP
