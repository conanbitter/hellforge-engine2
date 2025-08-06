#include "resources.hpp"
#include <fstream>
#include <stdexcept>

using namespace pixanv;
using namespace std::string_literals;

Texture pixanv::Resources::loadTexture(const std::string& filename)
{
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Can't open file "s + filename);
    }

    uint32_t width, height;
    uint8_t hasTransparency;

    infile.read(reinterpret_cast<char*>(&width), sizeof(width));
    infile.read(reinterpret_cast<char*>(&height), sizeof(height));
    infile.read(reinterpret_cast<char*>(&hasTransparency), sizeof(hasTransparency));

    Texture result(width, height);
    result.m_hasTransparency = hasTransparency == 1;
    if (result.m_hasTransparency) {
        infile.read(reinterpret_cast<char*>(&result.m_transparentColor), sizeof(result.m_transparentColor));
    } else {
        result.m_transparentColor = Color::BLACK;
    }

    infile.read(reinterpret_cast<char*>(result.m_data.data()), sizeof(Color) * width * height);

    infile.close();
    return result;
}