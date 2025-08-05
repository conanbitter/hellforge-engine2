#pragma once

#include <glad/gl.h>
#include "scaling.hpp"
#include "rendertarget.hpp"

namespace pixanv {
    class OpenGL {
    public:
        static void init(int width, int height);
        static void resize(int width, int height, const util::ScaleData& scaleData);
        static void free();
        static void present(const RenderTarget& rt);
    private:
        static GLuint program;
        static GLuint vao;
        static GLuint vbo;
        static GLuint frameTexture;
        static GLint scaleUniform;
    };
}