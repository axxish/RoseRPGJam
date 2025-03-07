#pragma once

#include <string>
#include <stdint.h>

struct AppConfig
{
    std::string name = "RoseRPG";
    uint16_t width = 800;
    uint16_t height = 600;
    uint16_t tileSize = 16;
    float minZoom = 0.5f;
    float maxZoom = 4.0f;
    float zoomSensitivity = 0.2f;
    float gameToRightMenuRatio = 0.75f;
    float gameToBottomMenuRatio = 0.8f;
};
