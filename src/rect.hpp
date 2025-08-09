#pragma once

#include "imagebuffer.hpp"

namespace pixanv {
    struct Rect {
        int left;
        int right;
        int top;
        int bottom;

        Rect() = default;
        Rect(const ImageBuffer& image) :left(0), top(0), right(image.width() - 1), bottom(image.height() - 1) {}
        Rect(int x, int y, int width, int height) :left(x), top(y), right(x + width - 1), bottom(y + height - 1) {}

        int x() const { return left; }
        int y() const { return top; }
        int width() const { return right - left + 1; }
        int height() const { return bottom - top + 1; }
    };
}