#include "text.hpp"
#include "rendertarget.hpp"

using namespace pixanv;

pixanv::Text::Text(RenderTarget& canvas) :m_gfx{ canvas }, std::ostream(this) {
    m_borderRight = m_gfx.width() - 1;
}

int pixanv::Text::overflow(int c)
{
    putc(c);
    return 0;
}

void pixanv::Text::putc(char c)
{
    if (c == '\n') {
        m_x = m_borderLeft;
        m_y += m_font->lineHeight;
        return;
    }
    const Texture& letter = m_font->getChar(c);
    m_gfx.blit(letter, m_x, m_y, m_color);
    m_x += letter.m_width + m_font->letterSpace;
    if (m_x > m_borderRight) {
        m_x = m_borderLeft;
        m_y += m_font->lineHeight;
    }
}

void pixanv::Text::print(const std::string& text) {
    if (m_font == nullptr)return;
    for (char c : text) {
        putc(c);
    }
}

void pixanv::Text::print(const char* text) {
    if (m_font == nullptr)return;
    for (const char* c = text;*c != '\0';c++) {
        putc(*c);
    }
}

void pixanv::Text::setXY(int x, int y) {
    m_x = x;
    m_y = y;
}

void pixanv::Text::setColor(Color color) {
    m_color = color;
}

void pixanv::Text::setFont(const Font* font) {
    m_font = font;
}

void pixanv::Text::setBorders(int left, int right)
{
    m_borderLeft = left;
    m_borderRight = right;
}

void pixanv::Text::resetBorders()
{
    m_borderLeft = 0;
    m_borderRight = m_gfx.width() - 1;
}
