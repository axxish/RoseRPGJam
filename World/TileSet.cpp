#include "Tileset.h"

TileSet::TileSet(const std::string &spritesheetPath, uint16_t spritesheetResolution)
{
    p_spriteSheet = new SpriteSheet(spritesheetPath, spritesheetResolution);
}

void TileSet::addTileType(const std::string &textureName, Sprite spriteInfo, bool isSolid)
{
    p_spriteSheet->AddSprite(textureName, spriteInfo);
    p_tileTypes.push_back(TileType(textureName, isSolid));
}
