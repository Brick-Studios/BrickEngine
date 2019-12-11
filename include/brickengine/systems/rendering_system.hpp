#ifndef FILE_RENDERING_SYSTEM_HPP
#define FILE_RENDERING_SYSTEM_HPP

#include <memory>
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/systems/system.hpp"

class RenderingSystem : public System {
public:
    RenderingSystem(std::shared_ptr<EntityManager>, Renderer& renderer);
    void update(double deltatime);
private:
    Renderer& renderer;
};

#endif // FILE_RENDERING_SYSTEM_HPP
