#ifndef FILE_COLOR_HPP
#define FILE_COLOR_HPP
struct Color
{
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
    unsigned short int a;
    bool operator==(const Color& other)
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    bool operator!=(const Color& other)
    {
        return r == other.r || g == other.g || b == other.b || a == other.a;
    }
};
#endif