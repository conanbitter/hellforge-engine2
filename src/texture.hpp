#pragma once

#include "imagebuffer.hpp"

namespace pixanv {

    class Texture :public ImageBuffer
    {
    public:
        using ImageBuffer::ImageBuffer;

        Color getTransparentColor() const { return m_transparentColor; }
        bool hasTransparency() const { return m_hasTransparency; }
        bool isTransparent(int x, int y);

    private:
        bool m_hasTransparency;
        Color m_transparentColor;

        friend class Resources;
        friend class RenderTarget;
    };

}