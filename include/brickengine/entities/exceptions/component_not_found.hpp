#ifndef FILE_COMPONENT_NOT_FOUND_EXCEPTION_HPP
#define FILE_COMPONENT_NOT_FOUND_EXCEPTION_HPP

#include <iostream>
#include <exception>

class ComponentNotFoundException : public std::exception {
private:
  std::string m_msg;
public:
  ComponentNotFoundException() : m_msg(std::string("The given entity id does not exist.")){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_ENTITY_NOT_FOUND_EXCEPTION_HPP