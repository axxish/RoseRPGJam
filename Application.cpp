#include "Application.h"
#include "Graphics/SpriteSheet.h"
#include "World/Tilemap.h"
#include <iostream>

Application::Application(const AppConfig &config)
    : p_appConfig(config), p_gameWindow(config.widthInTiles, config.heightInTiles, config.tileSize * config.scale)
{
}

Application::~Application()
{
}

void Application::Loop()
{
    float deltaTime = GetFrameTime();

    OnUpdate(deltaTime);
    OnRender();
}

void Application::Run()
{

    int cameraX = 1;
    int cameraY = 1;

    InitWindow(p_appConfig.widthInTiles * p_appConfig.tileSize * p_appConfig.scale,
               p_appConfig.heightInTiles * p_appConfig.tileSize * p_appConfig.scale, p_appConfig.name.c_str());
    SetTargetFPS(144);
    SetExitKey(0);

    p_uiSpriteSheet = new SpriteSheet("resources/iconsui.png", p_appConfig.tileSize);
    p_uiSpriteSheet->AddSprite("random", {4, 1, 1, 1});

    p_worldTileSet = TileSet("resources/maptiles.png", p_appConfig.tileSize);
    p_worldTileSet.addTileType("air", {1, 7, 1, 1}, false);
    p_worldTileSet.addTileType("floor", {3, 3, 1, 1}, false);
    p_worldTileSet.addTileType("wall", {1, 1, 1, 1}, true);

    p_entSpriteSheet = new SpriteSheet("resources/creatures.png", p_appConfig.tileSize);

    p_entSpriteSheet->AddSprite("hero", {0, 0, 1, 1});
    p_entSpriteSheet->AddSprite("rat", {1, 1, 1, 1});
    p_entSpriteSheet->AddSprite("200", {6, 1, 1, 1});

    p_itemSpriteSheet = new SpriteSheet("resources/items.png", p_appConfig.tileSize);

    p_itemSpriteSheet->AddSprite("sword", {1, 7, 1, 1});

    p_world.Init(20, 20, &p_worldTileSet, p_entSpriteSheet, p_itemSpriteSheet);

    currentItemInv = 0;

    p_gameWindow.Init();

    p_world.Camera = {{(float)(p_gameWindow.GetWidthInPixels() / 2), (float)(p_gameWindow.GetHeightInPixels() / 2)},
                      (float)(cameraX * 16 * p_appConfig.scale),
                      (float)(cameraY * 16 * p_appConfig.scale),
                      0,
                      1.0};

    while (!WindowShouldClose())
    {
        Loop();
    }

    CloseWindow();
}

void Application::OnRender()
{

    p_gameWindow.BeginMode();
    BeginMode2D(p_world.Camera);

    p_world.OnRender(p_gameWindow);

    EndMode2D();

    DrawInGameUI();

    p_gameWindow.EndMode();

    p_gameWindow.Render(0, 0, 1);

    // DrawTexture(*p_world.p_entSpriteSheet.GetTexture(), 0, 0, WHITE);
}

void Application::DrawInGameUI()
{
    auto player = p_world.Entities[0];
    if (!player)
        return;
    if (p_world.GetIsItPlayerMove() == false)
    {
        p_gameWindow.DrawSprite(*p_uiSpriteSheet, "random", (p_appConfig.widthInTiles - 1),
                                (p_appConfig.heightInTiles - 1));
    }

    for (int i = 0; i < 4; i++)
    {
        DrawRectangle(2 * 3, (3 + i) * 16 * 3 + 1 * 3, 12 * 3, 12 * 3, GRAY);
        if (inventoryOpen && (i == currentItemInv))
        {
            DrawRectangle(2 * 3, (3 + i) * 16 * 3 + 1 * 3, 12 * 3, 12 * 3, RED);
            if ((i < player->Inventory.size()))
            {
                DrawText("Q - DROP", 16 * 3, (3 + i) * 16 * 3, 12, WHITE);
            }
        }
    }

    int i = 0;
    for (auto item : player->Inventory)
    {

        p_gameWindow.DrawSprite(*p_itemSpriteSheet, item.SpriteName, 0, 3 + (i));
        i++;
    }

    int barLength = 60;

    float healthPercentage = static_cast<float>(player->CurrentHP) / player->MaxHP;
    float manaPercentage = static_cast<float>(player->CurrentMana) / player->MaxMana;
    DrawRectangle(0, 0, barLength * 3, 8, GRAY);
    DrawRectangle(0, 0, barLength * 3, 8, GRAY);
    DrawRectangle(0, 0, healthPercentage * barLength * 3, 8, RED);
    DrawRectangle(0, 8, manaPercentage * barLength * 3, 8, BLUE);
    std::string lvlText = "LVL: ";

    lvlText += std::to_string(player->Lvl);

    DrawText(lvlText.c_str(), 0, 16, 16, YELLOW);
}

void Application::OnUpdate(float deltaTime)
{
    if (IsKeyPressed(KEY_I) && p_world.GetIsItPlayerMove())
    {
        inventoryOpen = !inventoryOpen;
    }
    if (!inventoryOpen)
        p_world.OnUpdate(deltaTime);
    else
    {
        if (IsKeyPressed(KEY_S))
        {
            currentItemInv++;
        }
        if (IsKeyPressed(KEY_W))
        {
            currentItemInv--;
        }
        if (IsKeyPressed(KEY_Q))
        {
            if (currentItemInv < p_world.Entities[0]->Inventory.size())
            {
                p_world.Entities[0]->DropItem(currentItemInv);
                inventoryOpen = false;
            }
        }
        currentItemInv = currentItemInv % 4;
    }
}