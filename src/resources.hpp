#pragma once

#include <string>
#include "texture.hpp"
#include "font.hpp"

namespace pixanv {

    class Resources {
    public:
        static Texture loadTexture(const std::string& filename);
        static Font loadFont(const std::string& filename);
    };

}