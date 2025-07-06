#include "AtlasTexture.hpp"

#include <iostream>
#include <ostream>

AtlasTexture::AtlasTexture() : p_texture({}), p_resolution(0)
{

}


bool AtlasTexture::isValid() const {
    return p_texture.id > 0; // Check if the texture ID is valid (not zero)
}

AtlasTexture::AtlasTexture(const std::string& filePath, const int res){
    p_texture = LoadTexture(filePath.c_str());
    p_resolution = res;
}

AtlasTexture::~AtlasTexture() {
    if (isValid()) {
        UnloadTexture(p_texture); 
        p_texture = {};
    }
}

const Texture2D& AtlasTexture::get() const {
    return p_texture; // Return the texture
}

AtlasTexture::AtlasTexture(AtlasTexture &&other) noexcept : p_texture(other.p_texture), p_resolution(other.p_resolution)
{
    other.p_texture = {};
    other.p_resolution = 0;
}

AtlasTexture& AtlasTexture::operator=(AtlasTexture &&other) noexcept
{
    if (this == &other) {
        return *this;
    }

    // 2. Free any existing resource this object might be holding.
    if (isValid()) {
        UnloadTexture(p_texture);
    }

    // 3. Transfer ownership from the other object.
    p_texture = other.p_texture;
    p_resolution = other.p_resolution;

    // 4. Neuter the other object.
    other.p_texture = { 0 };
    other.p_resolution = 0;

    return *this;
}
