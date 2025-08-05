#include "opengl.hpp"

#include "shaders.hpp"
#include <algorithm>

using namespace pixanv;

static const float quad[6][4] = {
    {-1.0f, -1.0f, 0.0f, 1.0f},
    {-1.0f, 1.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {-1.0f, -1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, -1.0f, 1.0f, 1.0f},
};

GLuint pixanv::OpenGL::program = 0;
GLuint pixanv::OpenGL::vao = 0;
GLuint pixanv::OpenGL::vbo = 0;
GLuint pixanv::OpenGL::frameTexture = 0;
GLint pixanv::OpenGL::scaleUniform = 0;

void pixanv::OpenGL::init(int width, int height) {
    GLint vert_loc, vertUV_loc, tex_loc;
    program = initShaders(vert_loc, vertUV_loc, tex_loc, scaleUniform);

    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(vert_loc);
    glVertexAttribPointer(vert_loc, 2, GL_FLOAT, false, 4 * 4, nullptr);
    glEnableVertexAttribArray(vertUV_loc);
    glVertexAttribPointer(vertUV_loc, 2, GL_FLOAT, false, 4 * 4, (const void*)(2 * 4));
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * 4, &quad, GL_STATIC_DRAW);

    glGenTextures(1, &frameTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, nullptr);

    glUseProgram(program);
    glUniform1i(tex_loc, 0);
    shadersScale(scaleUniform, 1.0f, 1.0f, 0.0f, 0.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void pixanv::OpenGL::resize(int width, int height, const util::ScaleData& scaleData) {
    glViewport(0, 0, width, height);
    shadersScale(
        scaleUniform,
        scaleData.scaleX,
        scaleData.scaleY,
        scaleData.offsetX,
        scaleData.offsetY);
}

void pixanv::OpenGL::free() {
    if (glIsTexture(frameTexture)) {
        glDeleteTextures(1, &frameTexture);
    }
    if (glIsBuffer(vbo)) {
        glDeleteBuffers(1, &vbo);
    }
    if (glIsVertexArray(vao)) {
        glDeleteVertexArrays(1, &vao);
    }
    if (glIsProgram(program)) {
        glDeleteProgram(program);
    }
}

void pixanv::OpenGL::present(const RenderTarget& rt) {
    glBindTexture(GL_TEXTURE_2D, frameTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rt.width(), rt.height(), GL_RGB, GL_UNSIGNED_SHORT_5_6_5, rt.m_data.data());
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}