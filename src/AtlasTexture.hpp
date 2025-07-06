#pragma once
#include <raylib.h>

#include <iostream>
#include <ostream>
#include <string>

class AtlasTexture{
    public:
        AtlasTexture();
        explicit AtlasTexture(const std::string& filePath, int resolution);
        AtlasTexture(const AtlasTexture& other) = delete; // Disable copy constructor
        AtlasTexture& operator=(const AtlasTexture& other) = delete; // Disable copy assignment
        AtlasTexture(AtlasTexture&& other) noexcept; // Move constructor
        AtlasTexture& operator=(AtlasTexture&& other) noexcept; // Move assignment
        const Texture2D& get() const;
        int getResolution() const
        {

            return p_resolution;
        }
        bool isValid() const;
        
    ~AtlasTexture();

    private:
        Texture2D p_texture{};
        int p_resolution;
};
