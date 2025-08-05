#include "opengl.hpp"
#include <glad/gl.h>

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

static GLuint program;
static GLuint vao;
static GLuint vbo;
static GLuint frameTexture;
static GLsizei frameWidth;
static GLsizei frameHeight;
static GLint scale;
static float frameAR;



void pixanv::initOpenGL(int width, int height) {
    GLint vert_loc, vertUV_loc, tex_loc;
    program = initShaders(vert_loc, vertUV_loc, tex_loc, scale);

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

    frameWidth = width;
    frameHeight = height;
    frameAR = (float)width / (float)height;

    glGenTextures(1, &frameTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth, frameHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, nullptr);

    glUseProgram(program);
    glUniform1i(tex_loc, 0);
    shadersScale(scale, 1.0f, 1.0f, 0.0f, 0.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void pixanv::resizeOpenGL(int width, int height, const util::ScaleData& scaleData) {
    glViewport(0, 0, width, height);
    shadersScale(
        scale,
        scaleData.scaleX,
        scaleData.scaleY,
        scaleData.offsetX,
        scaleData.offsetY);
}

void pixanv::freeOpenGL() {
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

void pixanv::presentOpenGL(const RenderTarget& rt) {
    glBindTexture(GL_TEXTURE_2D, frameTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rt.width(), rt.height(), GL_RGB, GL_UNSIGNED_SHORT_5_6_5, rt.data());
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}