#ifndef FILE_CLICK_SYSTEM_HPP
#define FILE_CLICK_SYSTEM_HPP

#include "brickengine/systems/system.hpp"

class ClickSystem : public System {
public:
    ClickSystem(std::shared_ptr<EntityManager>);
    void update(double delta_time);
private:
    std::shared_ptr<EntityManager> entity_manager;
};


#endif /* FILE_CLICK_SYSTEM_HPP */