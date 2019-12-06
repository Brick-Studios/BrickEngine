#ifndef FILE_SIGN_HPP
#define FILE_SIGN_HPP

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

#endif // FILE_SIGN_HPP