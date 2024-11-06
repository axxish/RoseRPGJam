#pragma once

#include "../Graphics/SpriteSheet.h"
#include "TileType.h"
#include <memory>

class Tilemap
{
  public:
    Tilemap(uint16_t width, uint16_t height);
    Tilemap()
    {
        p_width = 0;
        p_height = 0;
    }

    // since tiles are identified with numbers, the type for the tile array is simply int
    std::vector<uint16_t> tiles;

    uint16_t getWidth()
    {
        return p_width;
    }

    uint16_t getHeight()
    {
        return p_height;
    }

    void SetTile(int x, int y, uint16_t tile)
    {
        if (isValidPosition(x, y))
        {
            tiles[y * p_width + x] = tile;
        }
    }

    uint16_t GetTile(int x, int y) const
    {
        if (isValidPosition(x, y))
        {
            return tiles[y * p_width + x];
        }
        else
        {
          return 0;
        }
    }

  private:
    uint16_t p_width;
    uint16_t p_height;

  private:
    // Helper function to check if a given (x, y) position is within the tilemap bounds
    bool isValidPosition(int x, int y) const
    {
        return x >= 0 && x < p_width && y >= 0 && y < p_height;
    }
};
