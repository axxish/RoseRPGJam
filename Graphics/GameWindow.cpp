#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(float normalizedWidth, float normalizedHeight, AppConfig& appConfig) : p_normalizedWidth(normalizedWidth), 
p_normalizedHeight(normalizedHeight)
{
    p_appConfig = std::make_shared<AppConfig>(appConfig); 
    p_tileSize = p_appConfig->tileSize;
    UpdateDimensions();
    p_mode = false;
}


void GameWindow::Init()
{
    p_renderTex = LoadRenderTexture(p_width, p_height);
}

GameWindow::~GameWindow()
{
    UnloadRenderTexture(p_renderTex);
}

void GameWindow::Render(int x, int y, int scale)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(
        p_renderTex.texture, {0, 0, (float)p_renderTex.texture.width, (float)-p_renderTex.texture.height},
        {(float)x, (float)y, (float)p_renderTex.texture.width * scale, (float)p_renderTex.texture.height * scale},
        {0, 0}, 0, WHITE);
    DrawBorder(WHITE, 2);
    EndDrawing();
}

void GameWindow::DrawBorder(Color color, int thickness)
{
    DrawRectangleLines(0, 0, p_width, p_height, color);
    //DrawRectangleLines(thickness, thickness, p_width - 2 * thickness, p_height - 2 * thickness, color);
}

void GameWindow::DrawSprite(const SpriteSheet &sheet, const std::string &name, int x, int y)
{
    if (p_mode)
    {
        Sprite SpriteData = *sheet.GetSprite(name);
        Rectangle SpriteTransform = {(float)(SpriteData.x * sheet.GetTileSize()),
                                     (float)(SpriteData.y * sheet.GetTileSize()),
                                     (float)(SpriteData.width_in_tiles * sheet.GetTileSize()),
                                     (float)(SpriteData.height_in_tiles * sheet.GetTileSize())};

        DrawTexturePro(*sheet.GetTexture(), SpriteTransform,
                       {(float)x * p_tileSize, (float)y * p_tileSize, (float)p_tileSize, (float)p_tileSize}, {0, 0}, 0,
                       WHITE);
    }
    else
    {
        std::cout << "Error: you are not in the renderer mode;";
    }
}

void GameWindow::DrawSpriteGray(const SpriteSheet &sheet, const std::string &name, int x, int y)
{
    if (p_mode)
    {
        Sprite SpriteData = *sheet.GetSprite(name);
        Rectangle SpriteTransform = {(float)(SpriteData.x * sheet.GetTileSize()),
                                     (float)(SpriteData.y * sheet.GetTileSize()),
                                     (float)(SpriteData.width_in_tiles * sheet.GetTileSize()),
                                     (float)(SpriteData.height_in_tiles * sheet.GetTileSize())};

        DrawTexturePro(*sheet.GetTexture(), SpriteTransform,
                       {(float)x * p_tileSize, (float)y * p_tileSize, (float)p_tileSize, (float)p_tileSize}, {0, 0}, 0,
                       GRAY);
    }
    else
    {
        std::cout << "Error: you are not in the renderer mode;";
    }
}

void GameWindow::BeginMode()
{
    p_mode = true;

    BeginTextureMode(p_renderTex);
    ClearBackground(BLACK);
}

void GameWindow::EndMode()
{
    p_mode = false;
    EndTextureMode();
}

void GameWindow::HandleInput(float deltaTime, World &world)
{
    // Check if the mouse is over the game window
    Vector2 mousePosition = GetMousePosition();
    bool inWindow = mousePosition.x >= 0 && mousePosition.x < p_width && mousePosition.y >= 0 && mousePosition.y < p_height;
    if (inWindow)
    {
        // Handle camera zoom with middle scroll
        float zoomChange = GetMouseWheelMove();
        if (zoomChange != 0)
        {
            world.Camera.zoom += zoomChange * p_appConfig->zoomSensitivity * deltaTime * 60; // Adjust the zoom sensitivity as needed
            if (world.Camera.zoom < p_appConfig->minZoom)
                world.Camera.zoom = p_appConfig->minZoom; // Minimum zoom level
            if (world.Camera.zoom > p_appConfig->maxZoom)
                world.Camera.zoom = p_appConfig->maxZoom; // Maximum zoom level
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
    {
        if (!world.isDragging)
        {
            world.pivotCamera = mousePosition;
            if (inWindow) world.isDragging = true;
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        
        if (world.isDragging)
        {
            Vector2 newMousePosition = mousePosition;
            float deltaX = (world.pivotCamera.x - newMousePosition.x) / world.Camera.zoom;
            float deltaY = (world.pivotCamera.y - newMousePosition.y) / world.Camera.zoom;
            world.Camera.target.x += deltaX;
            world.Camera.target.y += deltaY;
            world.pivotCamera = newMousePosition;
        }
    }
    else
    {
        world.isDragging = false;
    }
}

void GameWindow::OnWindowResize()
{
    UpdateDimensions();
    UnloadRenderTexture(p_renderTex);
    p_renderTex = LoadRenderTexture(p_width, p_height);
}

void GameWindow::UpdateDimensions()
{
    p_width = static_cast<uint16_t>(GetScreenWidth() * p_normalizedWidth);
    p_height = static_cast<uint16_t>(GetScreenHeight() * p_normalizedHeight);
}

uint32_t GameWindow::GetWidthInPixels()
{
    return p_renderTex.texture.width;
}
uint32_t GameWindow::GetHeightInPixels()
{
    return p_renderTex.texture.height;
}