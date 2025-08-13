#pragma once

#include <string>
#include "font.hpp"

namespace pixanv {
    class RenderTarget;

    class Text {
    public:
        void print(const std::string& text);
        void print(const char* text);
        void setXY(int x, int y);
        void setColor(Color color);
        void setFont(const Font* font);

        void setBorders(int left, int right);
        void resetBorders();
    private:
        Text(RenderTarget& canvas);

        int m_x = 0;
        int m_y = 0;
        int m_borderLeft = 0;
        int m_borderRight;
        Color m_color = Color::WHITE;
        const Font* m_font = nullptr;
        RenderTarget& m_gfx;

        friend class RenderTarget;
    };
}