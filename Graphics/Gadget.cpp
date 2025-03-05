#include "Gadget.h"

Gadget::Gadget(float normalizedX, float normalizedY, float normalizedWidth, float normalizedHeight, std::shared_ptr<AppConfig> appConfig)
    : p_normalizedX(normalizedX), p_normalizedY(normalizedY), p_normalizedWidth(normalizedWidth), p_normalizedHeight(normalizedHeight), p_appConfig(appConfig)
{
}

Gadget::~Gadget()
{
    UnloadRenderTexture(p_renderTex);
}

void Gadget::OnWindowResize()
{
    UpdateDimensions();
    UnloadRenderTexture(p_renderTex);
    p_renderTex = LoadRenderTexture(p_width, p_height);
}

void Gadget::UpdateDimensions()
{
    uint16_t screenHeight = GetScreenHeight();
    p_x = static_cast<uint16_t>(screenHeight * p_normalizedX);
    p_y = static_cast<uint16_t>(screenHeight * p_normalizedY);
    p_width = static_cast<uint16_t>(screenHeight * p_normalizedWidth);
    p_height = static_cast<uint16_t>(screenHeight * p_normalizedHeight);
}

uint32_t Gadget::GetWidthInPixels() const
{
    return p_renderTex.texture.width;
}

uint32_t Gadget::GetHeightInPixels() const
{
    return p_renderTex.texture.height;
}

uint32_t Gadget::GetXInPixels() const
{
    return p_x;
}

uint32_t Gadget::GetYInPixels() const
{
    return p_y;
}