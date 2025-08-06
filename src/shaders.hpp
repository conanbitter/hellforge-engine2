#pragma once

#include <glad/gl.h>

namespace pixanv::shaders {

    GLuint init(GLint& vertex_pos, GLint& vertex_uv, GLint& texture, GLint& scale);
    void scale(GLint param, float x, float y, float xoffset, float yoffset);

}