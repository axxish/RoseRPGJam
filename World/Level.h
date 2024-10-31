#pragma once

#include "../Graphics/SpriteSheet.h"
#include "TileType.h"
#include <memory>



class Level
{
  public:
    Level( uint16_t width, uint16_t height);
    Level(){
      p_width = 0;
      p_height = 0;
    }

    

    //since tiles are identified with numbers, the type for the tile array is simply int
    std::vector<uint16_t> tiles; 

    uint16_t getWidth(){
        return p_width;
    }

    uint16_t getHeight(){
        return p_width;
    }

  private:
    uint16_t p_width;
    uint16_t p_height;
    
    
};
