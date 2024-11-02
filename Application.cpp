#include "Application.h"
#include "World/Tilemap.h"
#include "Graphics/SpriteSheet.h"
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
    p_world.Init(p_appConfig.tileSize , 8, 8);

    p_uiSpriteSheet = new SpriteSheet("resources/iconsui.png", p_appConfig.tileSize);
    p_uiSpriteSheet->AddSprite("random", {4, 1, 1, 1});

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


    //DrawUI
    

    if(p_world.GetIsItPlayerMove() == false){
        p_gameWindow.DrawSprite(*p_uiSpriteSheet, "random", p_appConfig.widthInTiles - 1,  p_appConfig.heightInTiles - 1);
    }

    p_gameWindow.EndMode();

    p_gameWindow.Render(0, 0, 1);
    // DrawTexture(*p_world.p_entSpriteSheet.GetTexture(), 0, 0, WHITE);
}

void Application::OnUpdate(float deltaTime)
{

    p_world.OnUpdate(deltaTime);
}