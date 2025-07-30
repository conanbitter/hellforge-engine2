#pragma once

void initOpenGL(int width, int height);
void resizeOpenGL(int width, int height);
void freeOpenGL();
void presentOpenGL(const void* data);