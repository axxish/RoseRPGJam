#include "Gadget.h"
#include <iostream>

Gadget::Gadget(float normalizedX, float normalizedY, float normalizedWidth, float normalizedHeight, std::shared_ptr<AppConfig> appConfig)
    : p_normalizedX(normalizedX), p_normalizedY(normalizedY), p_normalizedWidth(normalizedWidth), p_normalizedHeight(normalizedHeight), p_appConfig(appConfig)
{
    p_renderTex = std::make_shared<RenderTexture2D>();
}

void Gadget::Init()
{
    *p_renderTex = LoadRenderTexture(p_width, p_height);
    UpdateDimensions();
}

void Gadget::Render(int scale)
{
    DrawTexturePro(
        p_renderTex->texture, {(float)p_x, (float)p_y, (float)p_renderTex->texture.width, (float)-p_renderTex->texture.height},
        {(float)0, (float)0, (float)p_renderTex->texture.width * scale, (float)p_renderTex->texture.height * scale},
        {0, 0}, 0, WHITE);
    DrawBorder(WHITE, 2);
    
}

void Gadget::DrawBorder(Color color, int thickness)
{
    DrawRectangleLines(p_x, p_y, p_width, p_height, color);
}

Gadget::~Gadget()
{
    UnloadRenderTexture(*p_renderTex);
}

void Gadget::OnWindowResize()
{

    UpdateDimensions();
    std::cout<<"Gadget::OnWindowResize() "<< p_width<<" "<<p_height<<" " << p_x<<" "<<p_y<<"\n";
    UnloadRenderTexture(*p_renderTex);
    *p_renderTex = LoadRenderTexture(p_width, p_height);
}

void Gadget::UpdateDimensions()
{
    uint16_t screenWidth = GetScreenWidth();
    uint16_t screenHeight = GetScreenHeight();
    p_x = static_cast<uint16_t>(screenWidth * p_normalizedX);
    p_y = static_cast<uint16_t>(screenHeight * p_normalizedY);
    p_width = static_cast<uint16_t>(screenWidth * p_normalizedWidth);
    p_height = static_cast<uint16_t>(screenHeight * p_normalizedHeight);
}

uint32_t Gadget::GetWidthInPixels() const
{
    return p_renderTex->texture.width;
}

uint32_t Gadget::GetHeightInPixels() const
{
    return p_renderTex->texture.height;
}

uint32_t Gadget::GetXInPixels() const
{
    return p_x;
}

uint32_t Gadget::GetYInPixels() const
{
    return p_y;
}   