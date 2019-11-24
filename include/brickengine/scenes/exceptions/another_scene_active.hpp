#ifndef FILE_ANOTHER_SCENE_ACTIVE_EXCEPTION_HPP
#define FILE_ANOTHER_SCENE_ACTIVE_EXCEPTION_HPP

#include <iostream>
#include <exception>

class AnotherSceneActiveException : public std::exception {
private:
    std::string m_msg;
public:
    AnotherSceneActiveException() : m_msg(std::string("Another scene is currently active, destroy it first")){}

    virtual const char* what() const throw() {
        return m_msg.c_str();
    }
};

#endif // FILE_ANOTHER_SCENE_ACTIVE_EXCEPTION_HPP