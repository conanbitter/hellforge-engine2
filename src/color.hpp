#pragma once
#include <cstdint>

class Color {
public:
    Color() :value(0) {}
    Color(uint16_t raw) :value(raw) {}
    Color(int r, int g, int b);
    int r() const;
    int g() const;
    int b() const;
private:
    uint16_t value;
};