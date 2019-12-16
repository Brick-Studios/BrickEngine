#ifndef FILE_DIRECTION_HPP
#define FILE_DIRECTION_HPP

enum class Direction { 
    POSITIVE = 0, 
    NEGATIVE = 1
};

#include <iostream>
#include <exception>

class UnknownDirectionException : public std::exception {
private:
  std::string m_msg;
public:
  UnknownDirectionException(int layer) : m_msg(std::string("The entered direction ") + std::to_string(layer) + std::string(" is not supported")){}

  virtual const char* what() const throw() {
    return m_msg.c_str();
  }
};

class DirectionConverter {
public:
    static Direction convertInt(int i) {
        if (i < 0 || i > 1)
            throw UnknownDirectionException(i);
        return static_cast<Direction>(i);
    }
};

#endif //FILE_DIRECTION_HPP
