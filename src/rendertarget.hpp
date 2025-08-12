#pragma once
#include "imagebuffer.hpp"
#include "rect.hpp"
#include "texture.hpp"
#include "font.hpp"
#include <string>

namespace pixanv {
    class RenderTarget :public ImageBuffer {
    public:
        void blit(const Texture& src, int x, int y, Color color = Color::WHITE);
        void blit(const Texture& src, int x, int y, const Rect& srcRect, Color color = Color::WHITE);
        void blit(const Texture& src, const Rect& dstRect, Color color = Color::WHITE);
        void blit(const Texture& src, const Rect& srcRect, const Rect& dstRect, Color color = Color::WHITE);

        void print(const Font& font, int x, int y, const std::string& text, Color color = Color::WHITE);
        void print(const Font& font, const std::string& text, Color color = Color::WHITE);
        //void blit(const ImageBuffer& src, int x, int y);
        //void blit(const Sprite& sprite);
    private:
        void resize(int width, int height);
        void blitCopy(const Texture& src, int x, int y, const Rect& srcRect);
        void blitCopyTransparent(const Texture& src, int x, int y, const Rect& srcRect);
        void blitScaled(const Texture& src, const Rect& srcRect, const Rect& dstRect);
        void blitScaledTransparent(const Texture& src, const Rect& srcRect, const Rect& dstRect);
        void blitCopyColor(const Texture& src, int x, int y, const Rect& srcRect, Color color);
        void blitCopyTransparentColor(const Texture& src, int x, int y, const Rect& srcRect, Color color);
        void blitScaledColor(const Texture& src, const Rect& srcRect, const Rect& dstRect, Color color);
        void blitScaledTransparentColor(const Texture& src, const Rect& srcRect, const Rect& dstRect, Color color);

        int printPosX = 0;
        int printPosY = 0;

        friend class App;
        friend class OpenGL;
    };
}