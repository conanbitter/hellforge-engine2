#include "texture.hpp"

bool pixanv::Texture::isTransparent(int x, int y)
{
    return m_hasTransparency && pixel(x, y) == m_transparentColor;
}