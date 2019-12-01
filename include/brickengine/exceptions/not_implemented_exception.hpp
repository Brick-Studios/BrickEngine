#ifndef FILE_NOT_IMPLEMENTED_EXCEPTION_HPP
#define FILE_NOT_IMPLEMENTED_EXCEPTION_HPP

#include <iostream>
#include <exception>
#include <string>

class NotImplementedException : public std::exception {
private:
  std::string m_msg;
public:
  NotImplementedException(std::string s) : m_msg(std::string("Not implemented, message: ") + s){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_NOT_IMPLEMENTED_EXCEPTION_HPP