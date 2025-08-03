#include "rendertarget.hpp"

using namespace pixanv;

void RenderTarget::blit(const ImageBuffer& src, int x, int y) {
}

void RenderTarget::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}
