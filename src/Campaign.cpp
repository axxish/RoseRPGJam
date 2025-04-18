#include "Campaign.h"

#include <iostream>

#include "Graphics/SpriteSheet.h"
#include "World/Tilemap.h"

Campaign::Campaign(AppConfig &config)
    : p_appConfig(config), p_gameWindow(1, 1, std::make_shared<AppConfig>(config))
{
    // std::cout<<(int)config.width<<" "<<(int)config.height<<" "<<(int)config.tileSize<<"\n";
}

Campaign::~Campaign() {}

void Campaign::Loop()
{
    float deltaTime = GetFrameTime();
    if (IsWindowResized())
    {
        OnWindowResize();
    }
    OnUpdate(deltaTime);
    OnRender();
}

void Campaign::OnWindowResize()
{
    p_gameWindow.OnWindowResize();

    p_entityStatsGadget->OnWindowResize();
    p_appConfig.height = GetScreenHeight();
    p_appConfig.width = GetScreenWidth();
    p_world.Camera.offset = {(float)(p_gameWindow.GetWidthInPixels() / 2),
                             (float)(p_gameWindow.GetHeightInPixels() / 2)};
}

void Campaign::Run(const std::string &campaignPath)
{
    std::srand(std::time(nullptr));
    int cameraX = 1;
    int cameraY = 1;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(p_appConfig.width, p_appConfig.height, p_appConfig.name.c_str());
    SetTargetFPS(144);
    SetExitKey(0);

    std::string path = campaignPath + "/resources/textures.png";
    p_spriteSheet = std::make_shared<SpriteSheet>(path, 16);
    std::cout << campaignPath + "/resources/textures.png" << std::endl;

    p_spriteSheet->AddSprite("random", {4, 0, 1, 1});

    p_worldTileSet = std::make_shared<TileSet>(p_spriteSheet, 16);
    p_worldTileSet->addTileType("air", {0, 0, 1, 1}, false);
    p_worldTileSet->addTileType("floor", {2, 0, 1, 1}, false);
    p_worldTileSet->addTileType("wall", {1, 0, 1, 1}, true);
    p_worldTileSet->addTileType("debugBlue", {0, 5, 1, 1}, false);
    p_worldTileSet->addTileType("debugRed", {1, 5, 1, 1}, false);
    p_worldTileSet->addTileType("debugGreen", {2, 5, 1, 1}, false);
    p_worldTileSet->addTileType("debugYellow", {3, 5, 1, 1}, false);
    p_worldTileSet->addTileType("debugEmerald", {4, 5, 1, 1}, false);
    p_spriteSheet->AddSprite("hero", {3, 2, 1, 1});
    p_spriteSheet->AddSprite("rat", {0, 2, 1, 1});
    p_spriteSheet->AddSprite("door", {3, 0, 1, 1});
    p_spriteSheet->AddSprite("heal", {4, 2, 1, 1});
    p_spriteSheet->AddSprite("sword", {1, 3, 1, 1});
    p_spriteSheet->AddSprite("greatsword", {0, 3, 1, 1});
    p_spriteSheet->AddSprite("helm", {0, 1, 1, 1});
    p_spriteSheet->AddSprite("shield", {4, 1, 1, 1});
    
    p_world.Init(20, 20, p_worldTileSet, p_spriteSheet);

    p_gameWindow = GameWindow(p_appConfig.gameToRightMenuRatio, p_appConfig.gameToBottomMenuRatio,
                              std::make_shared<AppConfig>(p_appConfig));

    p_entityStatsGadget = std::make_unique<EntityStatsGadget>(EntityStatsGadget(
        p_appConfig.gameToRightMenuRatio, 0, (double)1 - p_appConfig.gameToRightMenuRatio,
        p_appConfig.statsToInventoryRatio, std::make_shared<AppConfig>(p_appConfig)));

    p_gameWindow.Init();
    p_entityStatsGadget->Init();

    p_world.Camera = {{(float)(p_gameWindow.GetWidthInPixels() / 2),
                       (float)(p_gameWindow.GetHeightInPixels() / 2)},
                      (float)(cameraX * 16),
                      (float)(cameraY * 16),
                      0,
                      1};

    p_world.OnMoveCameraToPlayer();
    p_world.Camera.zoom = 3;

    while (!WindowShouldClose())
    {
        Loop();
    }

    CloseWindow();
}

void Campaign::OnRender()
{
    p_gameWindow.BeginMode();
    BeginMode2D(p_world.Camera);

    p_world.OnRender(p_gameWindow);

    EndMode2D();

    DrawInGameUI();
    Vector2 tilePos = p_gameWindow.GetMouseTilePosition(p_world);
    if (tilePos.x != -1 && tilePos.y != -1)
    {
        p_gameWindow.DrawTileHighlight(tilePos.x, tilePos.y, YELLOW, p_world);
    }
    p_gameWindow.GetMouseTilePosition(p_world);


    p_gameWindow.EndMode();

    p_entityStatsGadget->DrawStats(*p_world.Entities[0]);

    BeginDrawing();
    ClearBackground(BLACK);

    p_gameWindow.Render(1);

    if (p_entityStatsGadget)
        p_entityStatsGadget->Render(1);

    EndDrawing();
}

void Campaign::DrawInGameUI()
{
    auto player = p_world.Entities[0];
    if (!player)
        return;
    if (p_world.GetIsItPlayerMove() == false)
    {
        p_gameWindow.DrawSprite(*p_spriteSheet, "random", (p_appConfig.width - 1),
                                (p_appConfig.height - 1));
    }
}

void Campaign::OnUpdate(float deltaTime)
{
    p_gameWindow.HandleInput(deltaTime, p_world);

    if (IsKeyPressed(KEY_R))
    {
        p_world.Descend();
    }
   
        p_world.OnUpdate(deltaTime);
    
}