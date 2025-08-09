#include "imagebuffer.hpp"
#include "rect.hpp"

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

void ImageBuffer::pixelRaw(int x, int y, Color color) {
    m_data[x + y * m_width] = color;
}

Color ImageBuffer::pixelRaw(int x, int y) const {
    return m_data[x + y * m_width];
}

void ImageBuffer::fill(Color color) {
    std::fill(m_data.begin(), m_data.end(), color);
}

bool ImageBuffer::cropRect(Rect& rect) {
    if (rect.left < 0) rect.left = 0;
    if (rect.right >= m_width) rect.right = m_width - 1;
    if (rect.top < 0) rect.top = 0;
    if (rect.bottom >= m_height) rect.bottom = m_height - 1;

    return (rect.right > rect.left) && (rect.bottom > rect.top);
}