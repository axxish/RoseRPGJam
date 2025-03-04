#pragma once

#include <raylib.h>
#include <stdint.h>
#include "SpriteSheet.h"
#include "../World/World.h"
#include "../AppConfig.h"

class GameWindow{

    public:
    GameWindow(float normalizedWidth, float normalizedHeight, AppConfig& appConfig);
    ~GameWindow();

    void Init();
    void DrawBorder(Color color, int thickness);
    void Render(int x, int y, int scale);

    void DrawSprite(const SpriteSheet& sheet, const std::string& name, int x, int y);
    void DrawSpriteGray(const SpriteSheet& sheet, const std::string& name, int x, int y);

    void BeginMode();
    void EndMode();

    void HandleInput(float deltaTime, World& world);

    void OnWindowResize();

    uint32_t GetWidthInPixels();
    uint32_t GetHeightInPixels();
    private:

    std::shared_ptr<AppConfig> p_appConfig;
    
    RenderTexture2D p_renderTex;
    uint16_t p_tileSize;
    bool p_mode = false; // this bool is used to check if the renderer is in drawing mode or not
    uint16_t p_width;
    uint16_t p_height;

    float p_normalizedWidth;
    float p_normalizedHeight;

    void UpdateDimensions();
    

};