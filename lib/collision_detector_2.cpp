#include "brickengine/collision_detector_2.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/std/sign.hpp"
#include <cmath>
#include <algorithm>


CollisionDetector2::CollisionDetector2(std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions,
                                       EntityManager& em) : em(em), is_trigger_tag_exceptions(is_trigger_tag_exceptions) {}

std::vector<Collision> CollisionDetector2::detectCollision(int entity_id) {
    auto physics = em.getComponent<PhysicsComponent>(entity_id);
    std::vector<Collision> collisions;
    if (physics->collision_detection == CollisionDetectionType::Discrete) {
        auto discrete_collisions = this->detectDiscreteCollision(entity_id);
        std::for_each(discrete_collisions.begin(), discrete_collisions.end(), [&collisions](DiscreteCollision& dc) {
            collisions.push_back(Collision(dc.opposite_id, dc.is_trigger));
        });
    } else if (physics->collision_detection == CollisionDetectionType::Continuous) {
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::X, Direction::NEGATIVE);
            if (collision.space_left >= 0 && collision.opposite_id && !collision.is_trigger) {
                collisions.push_back(Collision(*collision.opposite_id, collision.is_trigger));
            }
        }
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::X, Direction::POSITIVE);
            if (collision.space_left <= 0 && collision.opposite_id && !collision.is_trigger) {
                collisions.push_back(Collision(*collision.opposite_id, collision.is_trigger));
            }
        }
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::Y, Direction::NEGATIVE);
            if (collision.space_left >= 0 && collision.opposite_id && !collision.is_trigger) {
                collisions.push_back(Collision(*collision.opposite_id, collision.is_trigger));
            }
        }
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::Y, Direction::POSITIVE);
            if (collision.space_left <= 0 && collision.opposite_id && !collision.is_trigger) {
                collisions.push_back(Collision(*collision.opposite_id, collision.is_trigger));
            }
        }
    }
    return collisions;
}

bool CollisionDetector2::findDisplacementException(std::set<std::string> tags_1, std::set<std::string> tags_2) const {
    for (const std::string& tag_1 : tags_1) {
        if (is_trigger_tag_exceptions.count(tag_1)) {
            for (const std::string& tag_2 : tags_2) {
                if (is_trigger_tag_exceptions.at(tag_1).count(tag_2)) {
                    return true;
                }
            }
        }
    }
    for (const std::string& tag_2 : tags_2) {
        if (is_trigger_tag_exceptions.count(tag_2)) {
            for (const std::string& tag_1 : tags_1) {
                if (is_trigger_tag_exceptions.at(tag_2).count(tag_1)) {
                    return true;
                }
            }
        }
    }
    return false;
}


CollisionDetector2CacheInfo CollisionDetector2::getCacheInfo() const {
    return cache_info;
}

void CollisionDetector2::invalidateCache() {
    cache_info = CollisionDetector2CacheInfo();
    discrete_cache.clear();
    continuous_cache.clear();
}

std::vector<DiscreteCollision> CollisionDetector2::detectDiscreteCollision(int entity_id) {
    if (discrete_cache.count(entity_id)) {
        ++cache_info.discrete_cache_hits;
        return discrete_cache.at(entity_id);
    }

    auto entity_collider = em.getComponent<RectangleColliderComponent>(entity_id);
    auto [ entity_position, entity_scale ] = em.getAbsoluteTransform(entity_id);
    auto entity_parent = em.getParent(entity_id);
    auto entity_children = em.getChildren(entity_id);

    auto opposite_entities_with_collider = em.getEntitiesByComponent<RectangleColliderComponent>();

    std::vector<DiscreteCollision> collisions;

    for (auto& [ opposite_id, opposite_collider] : opposite_entities_with_collider) {
        // Can't collide with yourself
        if (opposite_id == entity_id) continue;
        auto [ opposite_position, opposite_scale ] = em.getAbsoluteTransform(opposite_id);
        // Can't collide with family
        if (entity_parent && *entity_parent == opposite_id) continue;
        if (entity_children.count(opposite_id)) continue;

        bool is_trigger = false;
        if (entity_collider->is_trigger || opposite_collider->is_trigger) {
            // If there are no is_trigger_exceptions for these colliding entities,
            // just continue, because is trigger needs to go through everything except
            // some things
            if (!findDisplacementException(em.getTags(entity_id),
                em.getTags(opposite_id)))
                is_trigger = true;
        }

        ++this->cache_info.discrete_calculated_counter;

        const double entity_half_x = (entity_scale.x * entity_collider->x_scale) / 2;
        const double entity_half_y = (entity_scale.y * entity_collider->y_scale) / 2;
        const double opposite_half_x = (opposite_scale.x * opposite_collider->x_scale) / 2;
        const double opposite_half_y = (opposite_scale.y * opposite_collider->y_scale) / 2;

        // Check if there is a collision in the x axis
        const double delta_x = entity_position.x - opposite_position.x;
        const double pos_x = (entity_half_x + opposite_half_x) - std::abs(delta_x);
        if (pos_x <= 0) continue;

        // Check if there is a collision in the y axis
        const double delta_y = entity_position.y - opposite_position.y;
        const double pos_y = (entity_half_y + opposite_half_y) - std::abs(delta_y);
        if (pos_y <= 0) continue;
        
        // x axis collision
        if (pos_x < pos_y) {
            const double sign_x = sign(delta_x);
            Position position = Position(opposite_position.x + (opposite_half_x * sign_x), entity_position.y);
            Position delta = Position(pos_x * sign_x, 0);
            Position normal = Position(sign_x, 0);
            collisions.emplace_back(opposite_id, is_trigger,
                                    position, delta, normal);
        } else { // y axis collision
            const double sign_y = sign(delta_y);
            Position position = Position(entity_position.x, opposite_position.y + (opposite_half_y * sign_y));
            Position delta = Position(0, pos_y * sign_y);
            Position normal = Position(0, sign_y);
            collisions.emplace_back(opposite_id, is_trigger,
                                    position, delta, normal);
        }
    }
    discrete_cache.insert({ entity_id, collisions });
    return collisions;
}

ContinuousCollision CollisionDetector2::detectContinuousCollision(int entity_id, Axis axis, Direction direction) {
    if (continuous_cache.count(entity_id) && continuous_cache.at(entity_id).count(axis)
        && continuous_cache.at(entity_id).at(axis).count(direction)) {
        ++cache_info.continuous_cache_hits;
        return continuous_cache.at(entity_id).at(axis).at(direction);
    }
    
    // We only support rectangles
    auto entity_collider = em.getComponent<RectangleColliderComponent>(entity_id);
    auto [ entity_position, entity_scale ] = em.getAbsoluteTransform(entity_id);
    auto entity_children = em.getChildren(entity_id);
    auto entity_parent = em.getParent(entity_id);

    auto opposite_entities_with_collider = em.getEntitiesByComponent<RectangleColliderComponent>();

    double space_left_start_value;
    if (direction == Direction::NEGATIVE)
        space_left_start_value = std::numeric_limits<double>::lowest();
    else
        space_left_start_value = std::numeric_limits<double>::infinity();

    ContinuousCollision collision { std::nullopt, false, space_left_start_value };

    for (auto& [ opposite_id, opposite_collider ] : opposite_entities_with_collider) {
        // You cannot collide with family
        if (entity_parent && *entity_parent == opposite_id) continue;
        if (entity_children.count(opposite_id)) continue;
        if (opposite_id == entity_id) continue;

        ++this->cache_info.continuous_calculations_counter;

        auto [ opposite_position, opposite_scale ] = em.getAbsoluteTransform(opposite_id);

        if (axis == Axis::X) {
            int entity_y_start = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);
            int entity_y_end = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);
            int opposite_y_start = opposite_position.y - ((opposite_scale.y * opposite_collider->y_scale) / 2);
            int opposite_y_end = opposite_position.y + ((opposite_scale.y * opposite_collider->y_scale) / 2);

            if (direction == Direction::POSITIVE) { // Right
                if (entity_y_start < opposite_y_end && opposite_y_start < entity_y_end) {
                    double opposite_hit_wall = opposite_position.x - ((opposite_scale.x * opposite_collider->x_scale) / 2);
                    double entity_hit_wall = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    bool is_trigger = false;
                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!findDisplacementException(em.getTags(entity_id),
                            em.getTags(*collision.opposite_id))) {
                            is_trigger = true;
                        }
                    }
                    if(difference >= 0 && (collision.space_left > difference || (collision.is_trigger && !is_trigger))) {
                        collision.is_trigger = is_trigger;
                        collision.space_left = difference;
                        collision.opposite_id = opposite_id;
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Left
                if (entity_y_start < opposite_y_end && opposite_y_start < entity_y_end) {
                    double opposite_hit_wall = opposite_position.x + ((opposite_scale.x * opposite_collider->x_scale) / 2);
                    double entity_hit_wall = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    bool is_trigger = false;
                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!findDisplacementException(em.getTags(entity_id),
                            em.getTags(*collision.opposite_id))) {
                            is_trigger = true;
                        }
                    }
                    if (difference <= 0 && (collision.space_left < difference || (collision.is_trigger && !is_trigger))) {
                        collision.is_trigger = is_trigger;
                        collision.space_left = difference;
                        collision.opposite_id = opposite_id;
                    }
                }
            }
        } else if (axis == Axis::Y) {
            int entity_x_start = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);
            int entity_x_end = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);
            int opposite_x_start = opposite_position.x - ((opposite_scale.x * opposite_collider->x_scale) / 2);
            int opposite_x_end = opposite_position.x + ((opposite_scale.x * opposite_collider->x_scale) / 2);

            if (direction == Direction::POSITIVE) { // Down
                if (entity_x_start < opposite_x_end && opposite_x_start < entity_x_end) {
                    double opposite_hit_wall = opposite_position.y - ((opposite_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    bool is_trigger = false;
                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!findDisplacementException(em.getTags(entity_id),
                            em.getTags(*collision.opposite_id))) {
                            is_trigger = true;
                        }
                    }
                    if (difference >= 0 && (collision.space_left > difference || (collision.is_trigger && !is_trigger))) {
                        collision.is_trigger = is_trigger;
                        collision.space_left = difference;
                        collision.opposite_id = opposite_id;
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Up
                if(entity_x_start < opposite_x_end && opposite_x_start < entity_x_end) {
                    double opposite_hit_wall = opposite_position.y + ((opposite_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    bool is_trigger = false;
                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!findDisplacementException(em.getTags(entity_id),
                            em.getTags(*collision.opposite_id))) {
                            is_trigger = true;
                        }
                    }
                    if (difference <= 0 &&  (collision.space_left < difference || (collision.is_trigger && !is_trigger))) {
                        collision.is_trigger = is_trigger;
                        collision.space_left = difference;
                        collision.opposite_id = opposite_id;
                    }
                } 
            }
        }
    }
    continuous_cache.insert({ entity_id, std::unordered_map<Axis, std::unordered_map<Direction, ContinuousCollision>>() });
    continuous_cache.at(entity_id).insert({ axis, std::unordered_map<Direction, ContinuousCollision>() });
    continuous_cache.at(entity_id).at(axis).insert({ direction, collision });
    return collision;
}