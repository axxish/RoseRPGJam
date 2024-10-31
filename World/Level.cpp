#include "Level.h"
Level::Level( uint16_t width, uint16_t height)
    : p_width(width), p_height(height)
{
    auto size = p_width * p_height;
    tiles.reserve(p_width * p_height);
    for(int i = 0; i < size; i++){
        tiles.push_back(0);
    }
}

