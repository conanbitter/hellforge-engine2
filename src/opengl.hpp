#pragma once

void initOpenGL(int width, int height);
void resizeOpenGL(int width, int height, bool integerScaling);
void freeOpenGL();
void presentOpenGL(const void* data);
void screenToFrame(int screenX, int screenY, int& frameX, int& frameY);