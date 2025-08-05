#pragma once

#include "scaling.hpp"
#include "rendertarget.hpp"

namespace pixanv {

    void initOpenGL(int width, int height);
    void resizeOpenGL(int width, int height, const util::ScaleData& scaleData);
    void freeOpenGL();
    void presentOpenGL(const RenderTarget& rt);

}