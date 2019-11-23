#ifndef FILE_RESET_ON_SET_STATE_NOT_SET_EXCEPTION_HPP
#define FILE_RESET_ON_SET_STATE_NOT_SET_EXCEPTION_HPP

#include <iostream>
#include <exception>

template<typename State>
class ResetOnSetStateNotSetException : public std::exception {
private:
  std::string m_msg;
public:
  ResetOnSetStateNotSetException(State s) : m_msg(std::string("reset_on_set_state in GameStateManager not correctly set for the upcomming state: ") + std::to_string((int)s)){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_RESET_ON_SET_STATE_NOT_SET_EXCEPTION_HPP