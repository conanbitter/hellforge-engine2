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

Font pixanv::Resources::loadFont(const std::string& filename)
{
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Can't open file "s + filename);
    }

    Font result;
    char endChar;
    uint16_t height, width, letterSpace;
    uint8_t hasTransparency;
    Color transparentColor;

    infile.read(reinterpret_cast<char*>(&result.codeOffset), sizeof(result.codeOffset));
    infile.read(reinterpret_cast<char*>(&endChar), sizeof(endChar));
    infile.read(reinterpret_cast<char*>(&result.fallbackChar), sizeof(result.fallbackChar));
    infile.read(reinterpret_cast<char*>(&letterSpace), sizeof(letterSpace));
    infile.read(reinterpret_cast<char*>(&height), sizeof(height));
    infile.read(reinterpret_cast<char*>(&hasTransparency), sizeof(hasTransparency));
    if (hasTransparency == 1) {
        infile.read(reinterpret_cast<char*>(&transparentColor), sizeof(transparentColor));
    } else {
        transparentColor = Color::BLACK;
    }

    result.letterSpace = letterSpace;
    int length = endChar - result.codeOffset + 1;
    result.fallbackChar -= result.codeOffset;
    result.letters.clear();
    result.letters.reserve(length);

    for (int i = 0;i < length;i++) {
        infile.read(reinterpret_cast<char*>(&width), sizeof(width));
        Texture& tex = result.letters.emplace_back(width, height);
        tex.m_hasTransparency = hasTransparency == 1;
        tex.m_transparentColor = transparentColor;
        infile.read(reinterpret_cast<char*>(tex.m_data.data()), sizeof(Color) * width * height);
    }

    return result;
}
