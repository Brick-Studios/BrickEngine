#ifndef FILE_ENTITY_NOT_FOUND_EXCEPTION_HPP
#define FILE_ENTITY_NOT_FOUND_EXCEPTION_HPP

#include <iostream>
#include <exception>

class EntityNotFoundException : public std::exception {
private:
  std::string m_msg;
public:
  EntityNotFoundException() : m_msg(std::string("The given entity id does not exist.")){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_ENTITY_NOT_FOUND_EXCEPTION_HPP