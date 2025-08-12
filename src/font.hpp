#pragma once

#include "texture.hpp"
#include <vector>

namespace pixanv {
    class Font
    {
    public:
        const Texture& getChar(char c) const;
    private:
        char codeOffset;
        char fallbackChar;
        int letterSpace;
        vector<Texture> letters;

        friend class Resources;
        friend class RenderTarget;
    };
}