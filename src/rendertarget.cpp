#include "rendertarget.hpp"

using namespace pixanv;

void RenderTarget::blit(const Texture& tex, int x, int y) {
    if (tex.hasTransparency()) {
        for (int py = 0;py < tex.height();py++) {
            for (int px = 0;px < tex.width();px++) {
                Color color = tex.pixel(px, py);
                if (color != tex.getTransparentColor()) {
                    pixelRaw(px + x, py + y, color);
                }
            }
        }
    } else {
        for (int py = 0;py < tex.height();py++) {
            for (int px = 0;px < tex.width();px++) {
                pixelRaw(px + x, py + y, tex.pixel(px, py));
            }
        }
    }
}

void RenderTarget::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}
