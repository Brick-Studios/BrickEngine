#ifndef FILE_COMPONENT_HPP
#define FILE_COMPONENT_HPP

#include <iostream>

class Component {
public:
    Component() = default;
    virtual ~Component() = default;

    virtual std::string getName() = 0;
};

#endif /* FILE_COMPONENT_HPP */