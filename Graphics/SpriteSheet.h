#pragma once
#include <raylib.h>
#include <unordered_map>
#include <string>

struct Sprite{
    uint16_t x, y, width_in_tiles, height_in_tiles;
};

class SpriteSheet{
    public:
    SpriteSheet(){
        
    }
    
    SpriteSheet(const std::string& texturePath, uint16_t tileSize);

    void AddSprite(const std::string& name, Sprite spriteInfo);

    const Sprite* GetSprite(const std::string& name) const;

    const Texture2D* GetTexture() const;

    const uint16_t GetTileSize() const; 

    ~SpriteSheet();

    private:
    Texture2D p_Texture;
    uint16_t p_tileSize;
    std::unordered_map<std::string, Sprite> p_spriteIndices;  
};