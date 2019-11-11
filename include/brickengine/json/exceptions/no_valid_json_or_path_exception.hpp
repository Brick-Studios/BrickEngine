#ifndef FILE_NO_VALID_JSON_OR_PATH_EXCEPTION_HPP
#define FILE_NO_VALID_JSON_OR_PATH_EXCEPTION_HPP

#include <iostream>
#include <exception>

class NoValidJsonOrPathException : public std::exception {
private:
  std::string m_msg;
public:
  NoValidJsonOrPathException() : m_msg(std::string("The path or JSON is not valid")){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_NO_VALID_JSON_OR_PATH_EXCEPTION_HPP