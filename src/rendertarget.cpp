#include "rendertarget.hpp"
#include <algorithm>

using namespace pixanv;

void RenderTarget::blitCopy(const Texture& src, int x, int y, const Rect& srcRect) {
    Rect dstRect(x, y, srcRect.width(), srcRect.height());
    Rect srcRectMod(srcRect);
    if (!cropRect(dstRect, srcRectMod)) return;
    for (int dy = dstRect.top, sy = srcRectMod.top; dy <= dstRect.bottom; dy++, sy++) {
        auto srcStart = src.m_data.begin() + srcRectMod.left + sy * src.m_width;
        auto srcEnd = srcStart + srcRectMod.width();
        auto dstStart = m_data.begin() + dstRect.left + dy * m_width;
        std::copy(srcStart, srcEnd, dstStart);
    }
}

void RenderTarget::blitCopyTransparent(const Texture& src, int x, int y, const Rect& srcRect) {
    Rect dstRect(x, y, srcRect.width(), srcRect.height());
    Rect srcRectMod(srcRect);
    if (!cropRect(dstRect, srcRectMod)) return;
    for (int dy = dstRect.top, sy = srcRectMod.top; dy <= dstRect.bottom; dy++, sy++) {
        for (int dx = dstRect.left, sx = srcRectMod.left;dx <= dstRect.right;dx++, sx++) {
            Color color = src.pixel(sx, sy);
            if (color != src.m_transparentColor) {
                pixelRaw(dx, dy, color);
            }
        }
    }
}

void RenderTarget::blit(const Texture& tex, int x, int y) {
    Rect srcRect(tex);
    if (tex.hasTransparency()) {
        blitCopyTransparent(tex, x, y, srcRect);
    } else {
        blitCopy(tex, x, y, srcRect);
    }

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
