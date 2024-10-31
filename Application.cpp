#include "Application.h"
#include "World/Level.h"
#include <iostream>

Application::Application(const AppConfig &config)
    : p_appConfig(config), p_gameWindow(config.widthInTiles, config.heightInTiles, config.tileSize)
{
}

Application::~Application()
{
}

void Application::Loop()
{
    OnUpdate();
    OnRender();
}

void Application::Run()
{
    int cameraX = 1;
    int cameraY = 1;

    InitWindow(p_appConfig.widthInTiles * p_appConfig.tileSize * p_appConfig.scale,
               p_appConfig.heightInTiles * p_appConfig.tileSize * p_appConfig.scale, p_appConfig.name.c_str());
    SetTargetFPS(144);
    p_gameWindow.Init();
    p_worldTileSet = TileSet("resources/maptiles.png", p_appConfig.tileSize);
    p_worldTileSet.addTileType("air", {1, 7, 1, 1}, false);
    p_worldTileSet.addTileType("floor", {3, 3, 1, 1}, false);
    p_worldTileSet.addTileType("wall", {1, 1, 1, 1}, true);

    p_entSpriteSheet = SpriteSheet("resources/creatures.png", p_appConfig.tileSize);
    p_entSpriteSheet.AddSprite("hero", {0, 0, 1, 1});

    p_currentLevel = Level(16, 12);
    p_currentLevel.tiles = testWorld;

    p_camera = {{(float)(p_gameWindow.GetWidthInPixels() / 2), (float)(p_gameWindow.GetHeightInPixels() / 2)},
                (float)(cameraX * 16),
                (float)(cameraY * 16),
                0,
                1.0};

    while (!WindowShouldClose())
    {
        Loop();
    }

    CloseWindow();
}

void drawLevel(Level &level, GameWindow &renderer, TileSet &tileset)
{
    std::vector<TileType> types = tileset.getTileTypes();
    std::vector<uint16_t> tiles = level.tiles;

    int width = level.getWidth();
    int height = level.getHeight();
    int y = 0;

    for (int i = 0, x = 0; i < tiles.size(); i++, x++)
    {
        // if the iterator is greater than the width we go to next line
        if (x >= width)
        {
            y++;
            x = 0;
        }
        renderer.DrawSprite(tileset.getSpriteSheet(), types[tiles[i]].getTextureName(), x, y);
    }
}

void Application::OnRender()
{
    p_gameWindow.BeginMode();
    BeginMode2D(p_camera);

    drawLevel(p_currentLevel, p_gameWindow, p_worldTileSet);

    // DrawTexture(test, 50, 50, WHITE);
    EndMode2D();
    p_gameWindow.EndMode();

    p_gameWindow.Render(0, 0, p_appConfig.scale);
}

void Application::OnUpdate()
{
}