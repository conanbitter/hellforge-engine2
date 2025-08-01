#include "color.hpp"
#include <vector>

using std::vector;

class ImageBuffer {
public:
    ImageBuffer(int width, int height) :m_width(width), m_height(height), m_data(width* height) {}

    // pixel access with bound checks
    void pixel(int x, int y, Color color);
    Color pixel(int x, int y) const;
    // raw pixel access without bound checks
    Color& operator[](int x, int y);
    const Color& operator[](int x, int y) const;

    int width() const { return m_width; };
    int height() const { return m_height; };

protected:
    int m_width;
    int m_height;
    vector<Color> m_data;
};