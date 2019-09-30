
#include "brickengine/entity_factory.hpp"
#include "brickengine/components/component.hpp"
#include "brickengine/entities/entity_manager.hpp"

EntityFactory::EntityFactory(std::shared_ptr<EntityManager> _entityManager){
    entityManager = std::make_shared<EntityManager>(&_entityManager);
}

int EntityFactory::createDefault(){
    return entityManager->createEntity(
        std::vector<Component>{Component{}}
    );
}

EntityFactory::~EntityFactory(){

}