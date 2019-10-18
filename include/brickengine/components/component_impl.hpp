#ifndef FILE_COMPONENT_IMPL_HPP
#define FILE_COMPONENT_IMPL_HPP
#include <iostream>
#include "brickengine/components/component.hpp"

template<class ComponentType>
class ComponentImpl : public Component
{
public:
    virtual std::string getName()
    {
        return ComponentType::getNameStatic();
    }
};
#endif /* FILE_COMPONENT_IMPL_HPP */