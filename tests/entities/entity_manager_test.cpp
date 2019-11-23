#include <gtest/gtest.h>
#include "brickengine/entities/entity_manager.hpp"

#include "brickengine/components/component.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/player_component.hpp"

TEST(EntityManager, create_entity_and_get_comp) {
    EntityManager em;
    auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
    comps->push_back(std::make_unique<PhysicsComponent>(0, 0, 0, 0, false, Kinematic::IS_NOT_KINEMATIC, false, false));
    int id = em.createEntity(std::move(comps), std::nullopt);

    auto comp = em.getComponent<TransformComponent>(id);
    
    EXPECT_NE(nullptr, comp);
}

TEST(EntityManager, create_entities_and_get_all_entities_by_comp) {
    EntityManager em;
    {
        auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
        comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
        em.createEntity(std::move(comps), std::nullopt);
    }
    {
        auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
        comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
        em.createEntity(std::move(comps), std::nullopt);
    }

    auto entities = em.getEntitiesByComponent<TransformComponent>();
    
    EXPECT_EQ(2, entities.size());
}

TEST(EntityManager, create_entity_and_remove_comp) {
    EntityManager em;
    auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
    int id = em.createEntity(std::move(comps), std::nullopt);

    em.removeComponentFromEntity<TransformComponent>(id);
    auto comp = em.getComponent<TransformComponent>(id);
    
    EXPECT_EQ(nullptr, comp);
}

TEST(EntityManager, create_entities_and_remove_one_comp) {
    EntityManager em;
    {
        auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
        comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
        em.createEntity(std::move(comps), std::nullopt);
    }
    {
        auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
        comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
        int id = em.createEntity(std::move(comps), std::nullopt);
        em.removeComponentFromEntity<TransformComponent>(id);
    }

    auto entities = em.getEntitiesByComponent<TransformComponent>();

    
    EXPECT_EQ(1, entities.size());
}

TEST(EntityManager, create_entities_and_remove_entity) {
    EntityManager em;
    {
        auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
        comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
        em.createEntity(std::move(comps), std::nullopt);
    }
    {
        auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
        comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
        int id = em.createEntity(std::move(comps), std::nullopt);
        em.removeEntity(id);
    }

    auto entities = em.getEntitiesByComponent<TransformComponent>();

    EXPECT_EQ(1, 1);
}

TEST(EntityManager, create_entities_and_add_component) {
    EntityManager em;
    int id;
    {
        auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
        comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
        id = em.createEntity(std::move(comps), std::nullopt);
    }
    {
        em.addComponentToEntity(id, std::make_unique<PlayerComponent>(0, "Panda 1"));
    }

    auto entities = em.getEntitiesByComponent<PlayerComponent>();
    
    EXPECT_EQ(1, entities.size());
}

TEST(EntityManager, add_component_that_already_exists) {
    EntityManager em;
    auto comps = std::make_unique<std::vector<std::unique_ptr<Component>>>();
    comps->push_back(std::make_unique<TransformComponent>(0, 0, 0, 0, Direction::NEGATIVE, Direction::NEGATIVE));
    int id =em.createEntity(std::move(comps), std::nullopt);

    em.addComponentToEntity(id, std::make_unique<TransformComponent>(1, 1, 1, 1, Direction::NEGATIVE, Direction::NEGATIVE));

    auto x = em.getComponent<TransformComponent>(id);

    EXPECT_EQ(1, x->x_pos);
}
TEST(EntityManager, get_entities_when_component_is_not_used) {
    EntityManager em;

    auto entites = em.getEntitiesByComponent<TransformComponent>();

    EXPECT_EQ(0, entites.size());
}