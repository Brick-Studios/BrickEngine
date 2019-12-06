#ifndef FILE_FLOAT_POINT_COMPARER_HPP
#define FILE_FLOAT_POINT_COMPARER_HPP

#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>

class FloatingPointComparer {
public:
    static bool is_equal_to_zero(double f) {
        return std::fabs(f) < 1e-10;
    }
};

#endif // FILE_FLOATING_POINT_COMPARER_HPP