#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(uint16_t width, uint16_t height, uint16_t tileSize) : p_height(height), p_width(width)
{
    //p_renderTex = LoadRenderTexture(width * tileSize, height * tileSize);
    p_tileSize = tileSize;
}



GameWindow::~GameWindow()
{
    UnloadRenderTexture(p_renderTex);
}

void GameWindow::Render(int x, int y, int scale)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(p_renderTex.texture,
                   {0, 0, (float)p_renderTex.texture.width, (float)-p_renderTex.texture.height},
                   {(float)x, (float)y, (float)p_renderTex.texture.width * scale, (float)p_renderTex.texture.height * scale},
                   {0, 0}, 0, WHITE);
    EndDrawing();
}

void GameWindow::DrawSprite(const SpriteSheet& sheet, const std::string& name, int x, int y){
    if(p_mode){
        Sprite SpriteData = *sheet.GetSprite(name);
        Rectangle SpriteTransform = {
        (float)(SpriteData.x * sheet.GetTileSize()), 
        (float)(SpriteData.y * sheet.GetTileSize()), 
        (float)(SpriteData.width_in_tiles * sheet.GetTileSize()), 
        (float)(SpriteData.height_in_tiles * sheet.GetTileSize())};

        DrawTexturePro(*sheet.GetTexture(), SpriteTransform, {(float)x * p_tileSize, (float)y * p_tileSize, (float)p_tileSize, (float)p_tileSize}, {0, 0}, 0, WHITE);
    }
    else{
        std::cout <<"Error: you are not in the renderer mode;";
    }
}

void GameWindow::BeginMode()
{
    p_mode = true;
    BeginTextureMode(p_renderTex);
    ClearBackground(BLACK);
}

void GameWindow::EndMode()
{
    p_mode = false;
    EndTextureMode();
}
