#pragma once

#include <glad/gl.h>

GLuint initShaders(GLint& vertex_pos, GLint& vertex_uv, GLint& texture, GLint& scale);
void shadersScale(GLint param, float x, float y);