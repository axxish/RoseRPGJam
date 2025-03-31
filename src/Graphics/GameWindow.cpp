#include "GameWindow.h"

#include <iostream>

GameWindow::GameWindow(float normalizedWidth, float normalizedHeight,
                       std::shared_ptr<AppConfig> appConfig)
    : Gadget(0, 0, normalizedWidth, normalizedHeight, appConfig){
    p_tileSize = appConfig->tileSize;
    UpdateDimensions();
}


void GameWindow::Init()
{
    *p_renderTex =LoadRenderTexture(p_width, p_height);
    
}

void GameWindow::Render(int scale)
{
    DrawTexturePro(
        p_renderTex->texture, {(float)0, (float)0, (float)p_renderTex->texture.width,
       (float)-p_renderTex->texture.height},
        {(float)p_x, (float)p_y, (float)p_renderTex->texture.width * scale, (float)p_renderTex->texture.height * scale},
        {0, 0}, 0, WHITE);
    DrawBorder(WHITE, 2);
}

void GameWindow::DrawBorder(Color color, int thickness)
{
    DrawRectangleLines(0, 0, p_width, p_height, color);
}

Vector2 GameWindow::GetMouseTilePosition(const World &world) const
{
    // Get the current mouse position
    Vector2 mousePosition = GetMousePosition();

    // Check if the mouse is within the game window
    if (mousePosition.x < p_x || mousePosition.x >= p_x + p_width ||
        mousePosition.y < p_y || mousePosition.y >= p_y + p_height)
    {
        return {-1, -1}; // Return an invalid position if outside the window
    }

    // Adjust mouse position relative to the game window
    Vector2 adjustedMousePosition = {
        (mousePosition.x - p_x) / world.Camera.zoom,
        (mousePosition.y - p_y) / world.Camera.zoom
    };

    // Convert to world coordinates based on the camera's target and offset
    Vector2 worldPosition = {
        adjustedMousePosition.x + world.Camera.target.x - (p_width / 2.0f) / world.Camera.zoom,
        adjustedMousePosition.y + world.Camera.target.y - (p_height / 2.0f) / world.Camera.zoom
    };

    // Convert world position to tile coordinates
    Vector2 tilePosition = {
        static_cast<int>(worldPosition.x / p_tileSize),
        static_cast<int>(worldPosition.y / p_tileSize)
    };

    return tilePosition;
}

void GameWindow::DrawTileHighlight(int tileX, int tileY, Color color, const World &world) const
{
    // Calculate the position and size of the rectangle in screen space
    float rectX = p_x + (tileX * p_tileSize - world.Camera.target.x + (p_width / 2.0f) / world.Camera.zoom) * world.Camera.zoom;
    float rectY = p_y + (tileY * p_tileSize - world.Camera.target.y + (p_height / 2.0f) / world.Camera.zoom) * world.Camera.zoom;
    float rectSize = p_tileSize * world.Camera.zoom;

    // Draw the rectangle
    DrawRectangleLinesEx({rectX, rectY, rectSize, rectSize}, 1, color);
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

        DrawTexturePro(
            *sheet.GetTexture(), SpriteTransform,
            {(float)x * p_tileSize, (float)y * p_tileSize, (float)p_tileSize, (float)p_tileSize},
            {0, 0}, 0, WHITE);
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

        DrawTexturePro(
            *sheet.GetTexture(), SpriteTransform,
            {(float)x * p_tileSize, (float)y * p_tileSize, (float)p_tileSize, (float)p_tileSize},
            {0, 0}, 0, GRAY);
    }
    else
    {
        std::cout << "Error: you are not in the renderer mode;";
    }
}

void GameWindow::BeginMode()
{
    p_mode = true;
    BeginTextureMode(*p_renderTex);
    ClearBackground(BLACK);
}

void GameWindow::EndMode()
{
    p_mode = false;
    EndTextureMode();
}

void GameWindow::HandleInput(float deltaTime, World &world)
{
    Vector2 mousePosition = GetMousePosition();
    bool inWindow = mousePosition.x >= 0 && mousePosition.x < p_width && mousePosition.y >= 0 &&
                    mousePosition.y < p_height;
    if (inWindow)
    {
        float zoomChange = GetMouseWheelMove();
        if (zoomChange != 0)
        {
            world.Camera.zoom += zoomChange * p_appConfig->zoomSensitivity * deltaTime * 60;
            if (world.Camera.zoom < p_appConfig->minZoom)
                world.Camera.zoom = p_appConfig->minZoom;
            if (world.Camera.zoom > p_appConfig->maxZoom)
                world.Camera.zoom = p_appConfig->maxZoom;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
    {
        if (!world.isDragging)
        {
            world.pivotCamera = mousePosition;
            if (inWindow)
                world.isDragging = true;
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

void GameWindow::UpdateDimensions()
{
    p_x = 0;
    p_y = 0;
    p_width = static_cast<uint16_t>(GetScreenWidth() * p_normalizedWidth);
    p_height = static_cast<uint16_t>(GetScreenHeight() * p_normalizedHeight);
}
