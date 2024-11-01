#pragma once
#include "Graphics/GameWindow.h"
#include "World/TileSet.h"
#include "World/Tilemap.h"
#include "World/World.h"
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
    AppConfig p_appConfig;
    GameWindow p_gameWindow;

    

    World p_world;
    
};