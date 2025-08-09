#include "rendertarget.hpp"

using namespace pixanv;

void RenderTarget::blitCopy(const Texture& src, int x, int y, const Rect& srcRect) {
    Rect dstRect(x, y, srcRect.width(), srcRect.height());
    if (!cropRect(dstRect)) return;
    int offsetX = srcRect.left - x + dstRect.left;
    int offsetY = srcRect.top - y;
    for (int dy = dstRect.top; dy <= dstRect.bottom; dy++) {
        auto srcStart = src.m_data.begin() + offsetX + (dy + offsetY) * src.m_width;
        auto srcEnd = srcStart + dstRect.width();
        auto dstStart = m_data.begin() + dstRect.left + dy * m_width;
        std::copy(srcStart, srcEnd, dstStart);
    }
}

void RenderTarget::blit(const Texture& tex, int x, int y) {
    Rect srcRect(tex);
    blitCopy(tex, x, y, srcRect);
    /*Rect outrect(x, y, tex.width(), tex.height());

    if (!cropRect(outrect)) return;

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
    }*/
}

void RenderTarget::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}
