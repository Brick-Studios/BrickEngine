#ifndef FILE_CLICK_COMPONENT_HPP
#define FILE_CLICK_COMPONENT_HPP

#include <functional>
#include "brickengine/components/component_impl.hpp"

class ClickComponent : public ComponentImpl<ClickComponent> {
public:
    ClickComponent(std::function<void ()> fn, double xScale, double yScale);
    static std::string getNameStatic();

    std::function<void ()> fn;
    double xScale;
    double yScale;
};

#endif // FILE_CLICK_COMPONENT_HPP