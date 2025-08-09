#include "rendertarget.hpp"
#include <algorithm>

using namespace pixanv;

void RenderTarget::blitCopy(const Texture& src, int x, int y, const Rect& srcRect) {
    Rect dstRect(x, y, srcRect.width(), srcRect.height());
    Rect srcRectMod(srcRect);

    if (!cropRect(dstRect, srcRectMod)) return;
    if (!src.cropRect(srcRectMod, dstRect)) return;

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
    if (!src.cropRect(srcRectMod, dstRect)) return;

    for (int dy = dstRect.top, sy = srcRectMod.top; dy <= dstRect.bottom; dy++, sy++) {
        for (int dx = dstRect.left, sx = srcRectMod.left;dx <= dstRect.right;dx++, sx++) {
            Color color = src.pixel(sx, sy);
            if (color != src.m_transparentColor) {
                pixelRaw(dx, dy, color);
            }
        }
    }
}

void RenderTarget::blit(const Texture& src, int x, int y) {
    Rect srcRect(src);

    if (src.hasTransparency()) {
        blitCopyTransparent(src, x, y, srcRect);
    } else {
        blitCopy(src, x, y, srcRect);
    }
}

void RenderTarget::blit(const Texture& src, int x, int y, const Rect& srcRect) {
    if (src.hasTransparency()) {
        blitCopyTransparent(src, x, y, srcRect);
    } else {
        blitCopy(src, x, y, srcRect);
    }
}

void RenderTarget::blitScaled(const Texture& src, const Rect& srcRect, const Rect& dstRect) {
    float kx = (float)srcRect.width() / (float)(dstRect.width() - 1);
    float bx = (float)srcRect.left - kx * (float)dstRect.left;
    float ky = (float)srcRect.height() / (float)(dstRect.height() - 1);
    float by = (float)srcRect.top - ky * (float)dstRect.top;

    Rect dstRectMod(dstRect);
    cropRect(dstRectMod);
    Rect srcRectMod(srcRect);
    src.cropRect(srcRectMod);

    for (int dy = dstRectMod.top; dy <= dstRectMod.bottom; dy++) {
        for (int dx = dstRectMod.left;dx <= dstRectMod.right;dx++) {
            int sx = srcRectMod.clipX((float)dx * kx + bx);
            int sy = srcRectMod.clipY((float)dy * ky + by);
            pixelRaw(dx, dy, src.pixelRaw(sx, sy));
        }
    }
}

void RenderTarget::blitScaledTransparent(const Texture& src, const Rect& srcRect, const Rect& dstRect) {
    float kx = (float)srcRect.width() / (float)(dstRect.width() - 1);
    float bx = (float)srcRect.left - kx * (float)dstRect.left;
    float ky = (float)srcRect.height() / (float)(dstRect.height() - 1);
    float by = (float)srcRect.top - ky * (float)dstRect.top;

    Rect dstRectMod(dstRect);
    cropRect(dstRectMod);
    Rect srcRectMod(srcRect);
    src.cropRect(srcRectMod);

    for (int dy = dstRectMod.top; dy <= dstRectMod.bottom; dy++) {
        for (int dx = dstRectMod.left;dx <= dstRectMod.right;dx++) {
            int sx = srcRectMod.clipX((float)dx * kx + bx);
            int sy = srcRectMod.clipY((float)dy * ky + by);
            Color color = src.pixelRaw(sx, sy);
            if (color != src.m_transparentColor) {
                pixelRaw(dx, dy, color);
            }
        }
    }
}

void RenderTarget::blit(const Texture& src, const Rect& dstRect) {
    Rect srcRect(src);
    if (src.hasTransparency()) {
        blitScaledTransparent(src, srcRect, dstRect);
    } else {
        blitScaled(src, srcRect, dstRect);
    }
}

void RenderTarget::blit(const Texture& src, const Rect& srcRect, const Rect& dstRect) {
    if (src.hasTransparency()) {
        blitScaledTransparent(src, srcRect, dstRect);
    } else {
        blitScaled(src, srcRect, dstRect);
    }
}

void RenderTarget::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}
