#pragma once
#include <cstdint>

namespace pixanv {

#pragma pack(push, 1) 
    class Color {
    public:
        Color() :value(0) {}
        Color(uint16_t raw) :value(raw) {}
        Color(int r, int g, int b);
        int r() const;
        int g() const;
        int b() const;

        static const Color BLACK;
        static const Color WHITE;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
        static const Color CYAN;
        static const Color MAGENTA;
        static const Color YELLOW;

        bool operator==(const Color& rhs)const { return value == rhs.value; }
        Color operator*(const Color& rhs)const;
    private:
        uint16_t value;
    };
#pragma pack(pop)

}