#ifndef FILE_STATE_SYSTEMS_NOT_SET_EXCEPTION_HPP
#define FILE_STATE_SYSTEMS_NOT_SET_EXCEPTION_HPP

#include <iostream>
#include <exception>

template<typename State>
class StateSystemsNotSet : public std::exception {
private:
  std::string m_msg;
public:
  StateSystemsNotSet(State s) : m_msg(std::string("state_systems in GameStateManager not correctly set for the upcomming state: ") + std::to_string((int)s)){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

#endif // FILE_STATE_SYSTEMS_NOT_SET_EXCEPTION_HPP