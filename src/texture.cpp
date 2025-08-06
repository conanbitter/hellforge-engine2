#include "texture.hpp"

bool pixanv::Texture::isTransparent(int x, int y)
{
    return pixel(x, y) == m_transparentColor;
}