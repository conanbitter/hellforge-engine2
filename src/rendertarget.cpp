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

void RenderTarget::blitCopyColor(const Texture& src, int x, int y, const Rect& srcRect, Color color) {
    Rect dstRect(x, y, srcRect.width(), srcRect.height());
    Rect srcRectMod(srcRect);

    if (!cropRect(dstRect, srcRectMod)) return;
    if (!src.cropRect(srcRectMod, dstRect)) return;

    for (int dy = dstRect.top, sy = srcRectMod.top; dy <= dstRect.bottom; dy++, sy++) {
        for (int dx = dstRect.left, sx = srcRectMod.left;dx <= dstRect.right;dx++, sx++) {
            pixelRaw(dx, dy, src.pixel(sx, sy) * color);
        }
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

void RenderTarget::blitCopyTransparentColor(const Texture& src, int x, int y, const Rect& srcRect, Color color) {
    Rect dstRect(x, y, srcRect.width(), srcRect.height());
    Rect srcRectMod(srcRect);

    if (!cropRect(dstRect, srcRectMod)) return;
    if (!src.cropRect(srcRectMod, dstRect)) return;

    for (int dy = dstRect.top, sy = srcRectMod.top; dy <= dstRect.bottom; dy++, sy++) {
        for (int dx = dstRect.left, sx = srcRectMod.left;dx <= dstRect.right;dx++, sx++) {
            Color srcColor = src.pixel(sx, sy);
            if (srcColor != src.m_transparentColor) {
                pixelRaw(dx, dy, srcColor * color);
            }
        }
    }
}

void RenderTarget::blit(const Texture& src, int x, int y, Color color) {
    Rect srcRect(src);

    if (src.hasTransparency()) {
        if (color == Color::WHITE) {
            blitCopyTransparent(src, x, y, srcRect);
        } else {
            blitCopyTransparentColor(src, x, y, srcRect, color);
        }
    } else {
        if (color == Color::WHITE) {
            blitCopy(src, x, y, srcRect);
        } else {
            blitCopyColor(src, x, y, srcRect, color);
        }
    }
}

void RenderTarget::blit(const Texture& src, int x, int y, const Rect& srcRect, Color color) {
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

void RenderTarget::blitScaledColor(const Texture& src, const Rect& srcRect, const Rect& dstRect, Color color) {
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
            pixelRaw(dx, dy, src.pixelRaw(sx, sy) * color);
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

void RenderTarget::blitScaledTransparentColor(const Texture& src, const Rect& srcRect, const Rect& dstRect, Color color) {
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
            Color srcColor = src.pixelRaw(sx, sy);
            if (srcColor != src.m_transparentColor) {
                pixelRaw(dx, dy, srcColor * color);
            }
        }
    }
}

void RenderTarget::blit(const Texture& src, const Rect& dstRect, Color color) {
    Rect srcRect(src);
    if (src.hasTransparency()) {
        if (color == Color::WHITE) {
            blitScaledTransparent(src, srcRect, dstRect);
        } else {
            blitScaledTransparentColor(src, srcRect, dstRect, color);
        }
    } else {
        if (color == Color::WHITE) {
            blitScaled(src, srcRect, dstRect);
        } else {
            blitScaledColor(src, srcRect, dstRect, color);
        }
    }
}

void RenderTarget::blit(const Texture& src, const Rect& srcRect, const Rect& dstRect, Color color) {
    if (src.hasTransparency()) {
        if (color == Color::WHITE) {
            blitScaledTransparent(src, srcRect, dstRect);
        } else {
            blitScaledTransparentColor(src, srcRect, dstRect, color);
        }
    } else {
        if (color == Color::WHITE) {
            blitScaled(src, srcRect, dstRect);
        } else {
            blitScaledColor(src, srcRect, dstRect, color);
        }
    }
}

void pixanv::RenderTarget::print(const Font& font, int x, int y, const std::string& text, Color color)
{
    printPosX = x;
    printPosY = y;
    print(font, text, color);
}

void pixanv::RenderTarget::print(const Font& font, const std::string& text, Color color)
{
    for (char c : text) {
        const Texture& letter = font.getChar(c);
        blit(letter, printPosX, printPosY, color);
        printPosX += letter.m_width + font.letterSpace;
        if (printPosX >= m_width) break;
    }
}

void RenderTarget::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}

