#include "imagebuffer.hpp"

void ImageBuffer::pixel(int x, int y, Color color) {
    if (x<0 || x>m_width - 1 || y<0 || y>m_height - 1) return;
    m_data[x + y * m_width] = color;
}

Color ImageBuffer::pixel(int x, int y) const {
    if (x<0 || x>m_width - 1 || y<0 || y>m_height - 1) return Color(0);
    return m_data[x + y * m_width];
}

Color& ImageBuffer::operator[](int x, int y) {
    return m_data[x + y * m_width];
}

const Color& ImageBuffer::operator[](int x, int y) const {
    return m_data[x + y * m_width];
}