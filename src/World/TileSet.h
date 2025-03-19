#pragma once
#include "../Graphics/SpriteSheet.h"
#include "TileType.h"
#include <vector>
#include <memory>

class TileSet
{
  public:
    TileSet(){
      
    }

    TileSet(std::shared_ptr<SpriteSheet>, uint16_t spritesheetResolution);

    void addTileType(const std::string &textureName, Sprite spriteInfo, bool isSolid);

    const SpriteSheet &getSpriteSheet() const
    {
        return *p_spriteSheet;
    }

    const std::vector<TileType> getTileTypes() const
    {
        return p_tileTypes;
    }

  private:
    // the spritesheet associated to this tileset
    std::shared_ptr<SpriteSheet> p_spriteSheet;
    // for now, the tileTypes are simply associated with their vector index
    std::vector<TileType> p_tileTypes;
};