#pragma once
#include "Graphics/GameWindow.h"
#include "World/TileSet.h"
#include "World/Level.h"
#include <stdint.h>


struct AppConfig
{
    std::string name = "RoseRPG";
    uint8_t widthInTiles = 16;
    uint8_t heightInTiles = 9;
    uint8_t tileSize = 16;
    uint8_t scale = 3;
};

class Application
{
  public:
    Application(const AppConfig &config = AppConfig());
    ~Application();
    
    void Run();
    void OnUpdate();
    void OnRender();

  private:
    void Loop();
    Level p_currentLevel;
    AppConfig p_appConfig;
    GameWindow p_gameWindow;
    TileSet p_worldTileSet;
    SpriteSheet p_entSpriteSheet;
    Camera2D p_camera;

    std::vector<uint16_t> testWorld = {
        2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
};