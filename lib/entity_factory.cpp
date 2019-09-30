#include "brickengine/entity_factory.hpp"
#include "brickengine/components/component.hpp"
#include "brickengine/entities/entity_manager.hpp"

int EntityFactory::createDefault(){
    return entityManager->createEntity(
        std::vector<Component>{Component{}}
    );
}

EntityFactory::~EntityFactory(){

}
