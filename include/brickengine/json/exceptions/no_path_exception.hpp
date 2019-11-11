#ifndef FILE_NO_PATH_EXCEPTION_HPP
#define FILE_NO_PATH_EXCEPTION_HPP

#include <iostream>
#include <exception>

class NoPathException : public std::exception {
private:
  std::string m_msg;
public:
  NoPathException() : m_msg(std::string("String needs to be a valid path and confirmed via the boolean")){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_NO_PATH_EXCEPTION_HPP