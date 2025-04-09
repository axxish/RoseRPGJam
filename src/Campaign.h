#pragma once
#include "Graphics/GameWindow.h"
#include "Graphics/EntityStats.h"
#include "World/TileSet.h"
#include "World/Tilemap.h"
#include "World/World.h"
#include "AppConfig.h"

class Campaign
{
  public:
    Campaign(AppConfig &config = AppConfig());
    ~Campaign();

    void Run(const std::string& campaignPath);
    void OnWindowResize();
    void OnUpdate(float deltaTime);
    void OnRender();

    void DrawInGameUI();

  private:
    void Loop();

    bool worldRunning = true;
	
    AppConfig& p_appConfig;
    GameWindow p_gameWindow;
    std::unique_ptr<EntityStatsGadget> p_entityStatsGadget;

    std::shared_ptr<TileSet> p_worldTileSet;
    std::shared_ptr<SpriteSheet> p_spriteSheet;

    World p_world;
};