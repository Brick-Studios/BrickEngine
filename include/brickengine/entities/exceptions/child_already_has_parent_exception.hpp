#ifndef FILE_CHILD_ALREADY_HAS_PARENT_EXCEPTION_HPP
#define FILE_CHILD_ALREADY_HAS_PARENT_EXCEPTION_HPP

#include <iostream>
#include <exception>

class ChildAlreadyHasParentException : public std::exception {
private:
  std::string m_msg;
public:
  ChildAlreadyHasParentException() : m_msg(std::string("The given entity already has a parent.... kinda rude")){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_GRANDPARENTS_NOT_SUPPORTED_EXCEPTION_HPP