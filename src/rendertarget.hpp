#pragma once
#include "imagebuffer.hpp"
#include "texture.hpp"

namespace pixanv {
    struct Rect {
        int left;
        int right;
        int top;
        int bottom;

        int getX() const { return left; }
        int getY() const { return top; }
        int getWidth() const { return right - left + 1; }
        int getHeight() const { return bottom - top + 1; }
    };

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

        friend class App;
        friend class OpenGL;
    };
}