#include "font.hpp"

using namespace pixanv;

const Texture& pixanv::Font::getChar(char c) const
{
    if (c<codeOffset || c>codeOffset + letters.size() - 1 || letters[c - codeOffset].isEmpty()) return letters[fallbackChar];
    return letters[c - codeOffset];
}