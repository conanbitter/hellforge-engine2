#include "rendertarget.hpp"

using namespace pixanv;

void RenderTarget::blit(const Texture& tex, int x, int y) {
    Rect outrect{ .left = x,.right = x + tex.width() - 1,.top = y,.bottom = y + tex.height() - 1 };
    if (outrect.left < 0) outrect.left = 0;
    if (outrect.right >= m_width) outrect.right = m_width - 1;
    if (outrect.top < 0)outrect.top = 0;
    if (outrect.bottom >= m_height)outrect.bottom = m_height - 1;

    if (outrect.getWidth() <= 0 || outrect.getHeight() <= 0) return;

    if (tex.hasTransparency()) {
        for (int py = outrect.top;py <= outrect.bottom;py++) {
            for (int px = outrect.left;px <= outrect.right;px++) {
                Color color = tex.pixel(px - x, py - y);
                if (color != tex.getTransparentColor()) {
                    pixelRaw(px, py, color);
                }
            }
        }
    } else {
        for (int py = outrect.top;py <= outrect.bottom;py++) {
            for (int px = outrect.left;px <= outrect.right;px++) {
                pixelRaw(px, py, tex.pixel(px - x, py - y));
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
