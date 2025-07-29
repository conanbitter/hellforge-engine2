#include "color.hpp"

Color::Color(int r, int g, int b)
{
    value = (r & 0b11111) << 11 | (g & 0b111111) << 5 | (b & 0b11111);
}

int Color::r() const
{
    return value >> 11;
}

int Color::g() const
{
    return (value >> 5) & 0b111111;
}

int Color::b() const
{
    return value & 0b11111;
}
