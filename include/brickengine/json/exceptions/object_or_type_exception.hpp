#ifndef FILE_OBJECT_OR_TYPE_EXCEPTION_HPP
#define FILE_OBJECT_OR_TYPE_EXCEPTION_HPP

#include <iostream>
#include <exception>

class ObjectOrTypeException : public std::exception {
private:
  std::string m_msg;
public:
  ObjectOrTypeException(const std::string& bn) : m_msg(std::string("JSON object unknown or type mismatch calling type ") + bn){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_OBJECT_OR_TYPE_EXCEPTION_HPP