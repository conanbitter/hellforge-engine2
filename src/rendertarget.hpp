#pragma once
#include "imagebuffer.hpp"

namespace pixanv {
    class RenderTarget :public ImageBuffer {
    public:
        //void blit(const Texture& tex, int x, int y);
        void blit(const ImageBuffer& src, int x, int y);
        //void blit(const Sprite& sprite);
        //void print(int x, int y, const std::string& text, const Font& font);
    private:
        void resize(int width, int height);

        friend class App;
        friend class OpenGL;
    };
}