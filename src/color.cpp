#include "color.hpp"

using namespace pixanv;

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

const Color Color::BLACK = Color(0, 0, 0);
const Color Color::WHITE = Color(31, 63, 31);
const Color Color::RED = Color(31, 0, 0);
const Color Color::GREEN = Color(0, 63, 0);
const Color Color::BLUE = Color(0, 0, 31);
const Color Color::CYAN = Color(0, 63, 31);
const Color Color::MAGENTA = Color(31, 0, 31);
const Color Color::YELLOW = Color(31, 63, 0);