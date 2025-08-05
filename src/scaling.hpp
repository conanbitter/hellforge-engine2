#pragma once

namespace pixanv::util {
    struct ViewBox {
        int width;
        int height;
        int x;
        int y;
        int originalWidth;
        int originalHeight;

        void screenToView(int screenX, int screenY, int& viewX, int& viewY);
    };

    struct ScaleData {
        float scaleX;
        float scaleY;
        float offsetX;
        float offsetY;
    };

    void resizeView(int windowWidth, int windowHeight, int frameWidth, int frameHeight, bool integerScaling, ScaleData& scaleData, ViewBox& view);
}