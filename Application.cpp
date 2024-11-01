#include "Application.h"
#include "World/Tilemap.h"
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
    p_world.Init(16, 8, 8);
    p_gameWindow.Init();

    p_world.Camera = {{(float)(p_gameWindow.GetWidthInPixels() / 2), (float)(p_gameWindow.GetHeightInPixels() / 2)},
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

void Application::OnRender()
{
    p_gameWindow.BeginMode();
    BeginMode2D(p_world.Camera);

    p_world.OnRender(p_gameWindow);

    EndMode2D();
    p_gameWindow.EndMode();

    p_gameWindow.Render(0, 0, p_appConfig.scale);
    // DrawTexture(*p_world.p_entSpriteSheet.GetTexture(), 0, 0, WHITE);
}

void Application::OnUpdate()
{

    p_world.OnUpdate();
}