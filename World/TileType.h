#pragma once


#include <string>

class TileType{
    public:
    TileType(const std::string& textureName, bool solid) : 
    p_textureName(textureName), p_solid(solid){
    }

    TileType() = delete;

    bool isSolid(){
        return p_solid;
    }

    std::string getTextureName(){
        return p_textureName;
    }

    private:
    std::string p_textureName;
    bool p_solid;
};