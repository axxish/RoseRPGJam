#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const std::string& texturePath, uint16_t tileSize) {
    p_Texture = LoadTexture(texturePath.c_str());
    
    p_tileSize = tileSize;
}

void SpriteSheet::AddSprite(const std::string& name, Sprite spriteInfo) {
    p_spriteIndices[name] = spriteInfo;
}

const Sprite* SpriteSheet::GetSprite(const std::string& name) const{
    auto it = p_spriteIndices.find(name);
    if (it != p_spriteIndices.end()) {
        return &it->second;
    }

    return nullptr;
}

const Texture2D* SpriteSheet::GetTexture() const {
    return &p_Texture;
}

const uint16_t SpriteSheet::GetTileSize() const{
    return p_tileSize;
}

SpriteSheet::~SpriteSheet() {
    UnloadTexture(p_Texture);
}