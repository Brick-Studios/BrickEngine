#include <gtest/gtest.h>
#include "brickengine/entities/entity_manager.hpp"

#include "brickengine/components/component.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/player_component.hpp"

TEST(EntityManager_Family, create_entity_with_parent_already_relative) {
    EntityManager em;
    auto parent_comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    parent_comps->push_back(std::make_unique<TransformComponent>(50, 50, 2, 2, Direction::NEGATIVE, Direction::POSITIVE));
    int parent = em.createEntity(std::move(parent_comps), std::nullopt);

    auto child_comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    child_comps->push_back(std::make_unique<TransformComponent>(10, 5, 3, 2, Direction::NEGATIVE, Direction::NEGATIVE));
    int child = em.createEntity(std::move(child_comps), std::make_pair(parent, true));

    EXPECT_EQ(parent, em.getParent(child));
    EXPECT_EQ(10, em.getComponent<TransformComponent>(child)->xPos);
    EXPECT_EQ(5, em.getComponent<TransformComponent>(child)->yPos);
    EXPECT_EQ(3, em.getComponent<TransformComponent>(child)->xScale);
    EXPECT_EQ(2, em.getComponent<TransformComponent>(child)->yScale);
}
TEST(EntityManager_Family, create_entity_with_parent_not_yet_relative) {
    EntityManager em;
    auto parent_comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    parent_comps->push_back(std::make_unique<TransformComponent>(50, 50, 2, 2, Direction::NEGATIVE, Direction::POSITIVE));
    int parent = em.createEntity(std::move(parent_comps), std::nullopt);

    auto child_comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    child_comps->push_back(std::make_unique<TransformComponent>(10, 5, 3, 2, Direction::NEGATIVE, Direction::NEGATIVE));
    int child = em.createEntity(std::move(child_comps), std::make_pair(parent, false));

    EXPECT_EQ(parent, em.getParent(child));
    EXPECT_EQ(-40, em.getComponent<TransformComponent>(child)->xPos);
    EXPECT_EQ(-45, em.getComponent<TransformComponent>(child)->yPos);
    EXPECT_EQ(1.5, em.getComponent<TransformComponent>(child)->xScale);
    EXPECT_EQ(1, em.getComponent<TransformComponent>(child)->yScale);
}
TEST(EntityManager_Family, getAbsoluteTransform) {
    EntityManager em;
    auto grand_parent_comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    grand_parent_comps->push_back(std::make_unique<TransformComponent>(30, 10, 8, 10, Direction::NEGATIVE, Direction::POSITIVE));
    int grand_parent = em.createEntity(std::move(grand_parent_comps), std::nullopt);

    auto parent_comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    parent_comps->push_back(std::make_unique<TransformComponent>(50, 50, 2, 2, Direction::NEGATIVE, Direction::POSITIVE));
    int parent = em.createEntity(std::move(parent_comps), std::make_pair(grand_parent, false));

    auto child_comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    child_comps->push_back(std::make_unique<TransformComponent>(10, 5, 3, 2, Direction::NEGATIVE, Direction::NEGATIVE));

    ASSERT_ANY_THROW(em.createEntity(std::move(child_comps), std::make_pair(parent, false)));
}
