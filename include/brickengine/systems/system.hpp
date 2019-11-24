#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include "brickengine/entities/entity_manager.hpp"

class System {
public:
    System(std::shared_ptr<EntityManager> _entityManager) : entityManager(_entityManager) {}
    virtual ~System() = default;
    virtual void update(double deltatime) = 0;
    virtual void reset() {};
protected:
    std::shared_ptr<EntityManager> entityManager;
};

#endif /* FILE_SYSTEM_HPP */
