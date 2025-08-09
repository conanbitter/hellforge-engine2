#pragma once
#include "imagebuffer.hpp"
#include "rect.hpp"
#include "texture.hpp"

namespace pixanv {
    class RenderTarget :public ImageBuffer {
    public:
        void blit(const Texture& src, int x, int y);
        void blit(const Texture& src, int x, int y, const Rect& srcRect);
        void blit(const Texture& src, const Rect& dstRect);
        void blit(const Texture& src, const Rect& srcRect, const Rect& dstRect);
        //void blit(const ImageBuffer& src, int x, int y);
        //void blit(const Sprite& sprite);
        //void print(int x, int y, const std::string& text, const Font& font);
    private:
        void resize(int width, int height);
        void blitCopy(const Texture& src, int x, int y, const Rect& srcRect);

        friend class App;
        friend class OpenGL;
    };
}