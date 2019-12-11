#ifndef FILE_POSITION_HPP
#define FILE_POSITION_HPP

struct Position {
    Position(double x, double y) : x(x), y(y) {}
    double x, y;
};

#endif // FILE_POSITION_HPP