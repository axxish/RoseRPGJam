#pragma once

#include <raylib.h>
#include <stdint.h>
#include "SpriteSheet.h"

class GameWindow{

    public:
    GameWindow(uint16_t width, uint16_t height, uint16_t tileSize);
    ~GameWindow();

    void Init(){
        p_renderTex = LoadRenderTexture(p_width * p_tileSize, p_height * p_tileSize);
    }

    void Render(int x, int y, int scale);
    void DrawSprite(const SpriteSheet& sheet, const std::string& name, int x, int y);
    void DrawSpriteGray(const SpriteSheet& sheet, const std::string& name, int x, int y);

    void BeginMode();
    void EndMode();

    uint32_t GetWidthInPixels(){
        return p_renderTex.texture.width;
    }
    uint32_t GetHeightInPixels(){
        return p_renderTex.texture.height;
    }
    
    private:
    
    RenderTexture2D p_renderTex;
    uint16_t p_tileSize;
    bool p_mode = false;
    uint16_t p_width;
    uint16_t p_height;

};