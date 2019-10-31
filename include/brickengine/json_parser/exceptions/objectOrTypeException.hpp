#ifndef FILE_OBJECTORTPEEXCEPTION_HPP
#define FILE_OBJECTORTPEEXCEPTION_HPP

#include <iostream>
#include <exception>

class ObjectOrTypeException : public std::exception
{
  std::string m_msg;
public:

  ObjectOrTypeException(const std::string& bn)
    : m_msg(std::string("JSON object unknown or type mismatch calling type ") + bn)
  {}

  virtual const char* what() const throw()
  {
    return m_msg.c_str();
  }
};

#endif // FILE_OBJECTORTPEEXCEPTION_HPP