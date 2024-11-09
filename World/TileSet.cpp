#include "Tileset.h"
#include <memory>

TileSet::TileSet(std::shared_ptr<SpriteSheet> spritesheet, uint16_t spritesheetResolution)
{
    p_spriteSheet = spritesheet;
}

void TileSet::addTileType(const std::string &textureName, Sprite spriteInfo, bool isSolid)
{
    p_spriteSheet->AddSprite(textureName, spriteInfo);
    p_tileTypes.push_back(TileType(textureName, isSolid));
}
