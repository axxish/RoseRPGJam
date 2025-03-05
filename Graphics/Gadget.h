#pragma once

#include <raylib.h>
#include <stdint.h>
#include <memory>
#include "../AppConfig.h"

class Gadget
{
public:
    Gadget(float normalizedX, float normalizedY, float normalizedWidth, float normalizedHeight, std::shared_ptr<AppConfig> appConfig);
    virtual ~Gadget();

    virtual void Init() = 0;
    virtual void Render(int x, int y, int scale) = 0;
    virtual void OnWindowResize();

    uint32_t GetWidthInPixels() const;
    uint32_t GetHeightInPixels() const;
    uint32_t GetXInPixels() const;
    uint32_t GetYInPixels() const;

protected:
    std::shared_ptr<AppConfig> p_appConfig;
    RenderTexture2D p_renderTex;
    uint16_t p_width;
    uint16_t p_height;
    uint16_t p_x;
    uint16_t p_y;

    float p_normalizedX;
    float p_normalizedY;
    float p_normalizedWidth;
    float p_normalizedHeight;

    virtual void UpdateDimensions();
};