#ifndef FILE_CLICK_COMPONENT_HPP
#define FILE_CLICK_COMPONENT_HPP

#include <functional>
#include "brickengine/components/component_impl.hpp"

class ClickComponent : public ComponentImpl<ClickComponent> {
public:
    ClickComponent(std::function<void ()> fn);
    static std::string getNameStatic();

    std::function<void ()> fn;
};

#endif // FILE_CLICK_COMPONENT_HPP