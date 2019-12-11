#ifndef FILE_NO_SCENE_ACTIVE_EXCEPTION_HPP
#define FILE_NO_SCENE_ACTIVE_EXCEPTION_HPP

#include <iostream>
#include <exception>

class NoSceneActiveException : public std::exception {
private:
    std::string m_msg;
public:
    NoSceneActiveException() : m_msg(std::string("There is no scene active as the given SceneType.")){}

    virtual const char* what() const throw() {
        return m_msg.c_str();
    }
};

#endif // FILE_NO_SCENE_ACTIVE_EXCEPTION_HPP