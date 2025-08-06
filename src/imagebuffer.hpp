#pragma once

#include "color.hpp"
#include <vector>

using std::vector;

namespace pixanv {
    class ImageBuffer {
    public:
        ImageBuffer(int width, int height) :m_width(width), m_height(height), m_data(width* height) {}

        void pixel(int x, int y, Color color);
        Color pixel(int x, int y) const;
        void fill(Color color);

        int width() const { return m_width; };
        int height() const { return m_height; };

    protected:
        ImageBuffer() :m_width(0), m_height(0), m_data(0) {};
        int m_width;
        int m_height;
        vector<Color> m_data;
    };
}