#include "scaling.hpp"
#include <algorithm>

void pixanv::util::resizeView(int windowWidth, int windowHeight, int frameWidth, int frameHeight, bool integerScaling, ScaleData& scaleData, ViewBox& view)
{
    view.originalWidth = frameWidth;
    view.originalHeight = frameHeight;

    if (windowWidth % frameWidth == 0 && windowHeight % frameHeight == 0) {
        scaleData.scaleX = 1.0f;
        scaleData.scaleY = 1.0f;
        scaleData.offsetX = 0.0f;
        scaleData.offsetY = 0.0f;
        view.width = windowWidth;
        view.height = windowHeight;
        view.x = 0;
        view.y = 0;
    } else if (integerScaling) {
        int iscale = std::min(windowWidth / frameWidth, windowHeight / frameHeight);
        bool xoffset = (windowWidth - frameWidth * iscale) % 2 != 0;
        bool yoffset = (windowHeight - frameHeight * iscale) % 2 != 0;
        scaleData.scaleX = (float)(frameWidth * iscale) / (float)windowWidth;
        scaleData.scaleY = (float)(frameHeight * iscale) / (float)windowHeight;
        scaleData.offsetX = xoffset ? -1.0f / (float)windowWidth : 0.0f;
        scaleData.offsetY = yoffset ? -1.0f / (float)windowHeight : 0.0f;
        view.width = frameWidth * iscale;
        view.height = frameHeight * iscale;
        view.x = (windowWidth - view.width) / 2;
        view.y = (windowHeight - view.height) / 2;
    } else {
        float windowAR = (float)windowWidth / (float)windowHeight;
        float frameAR = (float)frameWidth / (float)frameHeight;
        if (frameAR < windowAR) {
            scaleData.scaleX = frameAR / windowAR;
            scaleData.scaleY = 1.0f;
            scaleData.offsetX = 0.0f;
            scaleData.offsetY = 0.0f;
            view.height = windowHeight;
            view.width = (float)windowHeight * frameAR;
            view.x = (windowWidth - view.width) / 2;
            view.y = 0;
        } else {
            scaleData.scaleX = 1.0f;
            scaleData.scaleY = windowAR / frameAR;
            scaleData.offsetX = 0.0f;
            scaleData.offsetY = 0.0f;
            view.width = windowWidth;
            view.height = (float)windowWidth / frameAR;
            view.x = 0;
            view.y = (windowHeight - view.height) / 2;
        }
    }
}

void pixanv::util::ViewBox::screenToView(int screenX, int screenY, int& viewX, int& viewY)
{
    viewX = (screenX - x) * originalWidth / width;
    viewY = (screenY - y) * originalHeight / height;
}
