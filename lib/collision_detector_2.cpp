#include "brickengine/collision_detector_2.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/player_component.hpp"
#include "brickengine/std/floating_point_comparer.hpp"
#include "brickengine/std/sign.hpp"
#include <cmath>
#include <algorithm>


CollisionDetector2::CollisionDetector2(std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions,
                                       EntityManager& em) : em(em), is_trigger_tag_exceptions(is_trigger_tag_exceptions) {}

std::vector<Collision> CollisionDetector2::detectCollision(int entity_id) {
    auto physics = em.getComponent<PhysicsComponent>(entity_id);
    std::vector<Collision> collisions;
    if (physics->collision_detection.isDiscrete()) {
        auto discrete_collisions = this->detectDiscreteCollision(entity_id);
        std::for_each(discrete_collisions.begin(), discrete_collisions.end(), [&collisions](DiscreteCollision& dc) {
            collisions.push_back(Collision(dc.opposite_id, dc.is_trigger));
        });
    }
    if (physics->collision_detection.isContinuous()) {
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::X, Direction::NEGATIVE);
            if ((collision.space_left > 0 || FloatingPointComparer::is_equal_to_zero(collision.space_left)) && collision.opposite_id) {
                collisions.push_back(Collision(*collision.opposite_id, false));
            }
        }
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::X, Direction::POSITIVE);
            if ((collision.space_left < 0 || FloatingPointComparer::is_equal_to_zero(collision.space_left)) && collision.opposite_id) {
                collisions.push_back(Collision(*collision.opposite_id, false));
            }
        }
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::Y, Direction::NEGATIVE);
            if ((collision.space_left > 0 || FloatingPointComparer::is_equal_to_zero(collision.space_left)) && collision.opposite_id) {
                collisions.push_back(Collision(*collision.opposite_id, false));
            }
        }
        {
            auto collision = this->detectContinuousCollision(entity_id, Axis::Y, Direction::POSITIVE);
            if ((collision.space_left < 0 || FloatingPointComparer::is_equal_to_zero(collision.space_left)) && collision.opposite_id) {
                collisions.push_back(Collision(*collision.opposite_id, false));
            }
        }
    }
    return collisions;
}

bool CollisionDetector2::hasTriggerException(std::set<std::string> tags_1, std::set<std::string> tags_2) const {
    // For every tag in tags_1
    for (const std::string& tag_1 : tags_1) {
        // Is the tag in the trigger_tag_exceptions?
        if (is_trigger_tag_exceptions.count(tag_1)) {
            // For every tag in tags_2
            for (const std::string& tag_2 : tags_2) {
                // If tag_2 is in the list of tags_1?
                if (is_trigger_tag_exceptions.at(tag_1).count(tag_2)) {
                    // This entity should not collide with this trigger
                    return true;
                }
            }
        }
    }
    // Same as above but other way around
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


CollisionDetector2Info CollisionDetector2::getInfo() const {
    return info;
}

void CollisionDetector2::invalidateInfo() {
    info = CollisionDetector2Info();
}

std::vector<DiscreteCollision> CollisionDetector2::detectDiscreteCollision(int entity_id) {
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
            // put is_trigger on true, because is_trigger needs to go through everything
            // except some things
            if (!hasTriggerException(em.getTags(entity_id),
                em.getTags(opposite_id)))
                is_trigger = true;
        }

        ++this->info.discrete_calculated_counter;

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
    return collisions;
}

ContinuousCollision CollisionDetector2::detectContinuousCollision(int entity_id, Axis axis, Direction direction) {
    // We only support rectangles
    auto entity_collider = em.getComponent<RectangleColliderComponent>(entity_id);
    auto [ entity_position, entity_scale ] = em.getAbsoluteTransform(entity_id);
    auto entity_children = em.getChildren(entity_id);
    auto entity_parent = em.getParent(entity_id);

    auto opposite_entities_with_collider = em.getEntitiesByComponent<RectangleColliderComponent>();

    double space_left_start_value = 0;
    if (direction == Direction::NEGATIVE)
        space_left_start_value = std::numeric_limits<double>::lowest();
    else
        space_left_start_value = std::numeric_limits<double>::infinity();

    std::optional<int> opposite_opt = std::nullopt;

    ContinuousCollision collision { opposite_opt, space_left_start_value };

    for (auto& [ opposite_id, opposite_collider ] : opposite_entities_with_collider) {
        // You cannot collide with family
        if (entity_parent && *entity_parent == opposite_id) continue;
        if (entity_children.count(opposite_id)) continue;
        if (opposite_id == entity_id) continue;

        ++this->info.continuous_calculations_counter;

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

                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!hasTriggerException(em.getTags(entity_id),
                            em.getTags(opposite_id))) {
                            continue;
                        }
                    }
                    if (difference >= 0 && collision.space_left > difference) {
                        collision.space_left = difference;
                        collision.opposite_id = opposite_id;
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Left
                if (entity_y_start < opposite_y_end && opposite_y_start < entity_y_end) {
                    double opposite_hit_wall = opposite_position.x + ((opposite_scale.x * opposite_collider->x_scale) / 2);
                    double entity_hit_wall = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);
                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!hasTriggerException(em.getTags(entity_id),
                            em.getTags(opposite_id))) {
                            continue;
                        }
                    }
                    if (difference <= 0 && collision.space_left < difference) {
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
                    double x = 0;
                    x++;
                    double opposite_hit_wall = opposite_position.y - ((opposite_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);
                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!hasTriggerException(em.getTags(entity_id),
                            em.getTags(opposite_id))) {
                            continue;
                        }
                    }
                    if (difference >= 0 && collision.space_left > difference) {
                        collision.space_left = difference;
                        collision.opposite_id = opposite_id;
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Up
                if(entity_x_start < opposite_x_end && opposite_x_start < entity_x_end) {
                    double opposite_hit_wall = opposite_position.y + ((opposite_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);
                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (entity_collider->is_trigger || opposite_collider->is_trigger) {
                        if (!hasTriggerException(em.getTags(entity_id),
                            em.getTags(opposite_id))) {
                            continue;
                        }
                    }
                    if (difference <= 0 &&  collision.space_left < difference) {
                        collision.space_left = difference;
                        collision.opposite_id = opposite_id;
                    }
                } 
            }
        }
    }
    return collision;
}
