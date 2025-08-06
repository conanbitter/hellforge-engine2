#pragma once

#include <string>
#include "texture.hpp"

namespace pixanv {

    class Resources {
    public:
        static Texture loadTexture(const std::string& filename);
    };

}