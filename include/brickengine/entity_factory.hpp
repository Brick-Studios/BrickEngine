#ifndef FILE_ENTITY_FACTORY_HPP
#define FILE_ENTITY_FACTORY_HPP

#include <vector>

#include "brickengine/entities/entity_manager.hpp"

class EntityFactory{
    public:
        EntityFactory(std::shared_ptr<EntityManager> _entityManager) : entityManager(_entityManager){
        };
        ~EntityFactory() = default;
    private:
        std::shared_ptr<EntityManager> entityManager;
};

#endif /* FILE_ENTITY_FACTORY_HPP */