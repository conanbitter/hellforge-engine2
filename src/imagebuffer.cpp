#include "imagebuffer.hpp"

using namespace pixanv;

void ImageBuffer::pixel(int x, int y, Color color) {
    if (x<0 || x>m_width - 1 || y<0 || y>m_height - 1) return;
    m_data[x + y * m_width] = color;
}

Color ImageBuffer::pixel(int x, int y) const {
    x %= m_width;
    if (x < 0) x += m_width;
    y %= m_height;
    if (y < 0)y += m_height;
    return m_data[x + y * m_width];
}

void ImageBuffer::fill(Color color) {
    std::fill(m_data.begin(), m_data.end(), color);
}