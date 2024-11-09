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
    void OnUpdate(float deltaTime);
    void OnRender();

    void DrawInGameUI();

  private:
    void Loop();

    bool worldRunning = true;
		
		uint16_t currentItemInv;
		bool inventoryOpen = false;

    AppConfig p_appConfig;
    GameWindow p_gameWindow;

    TileSet p_worldTileSet;
    std::shared_ptr<SpriteSheet> p_spriteSheet;

    World p_world;
};