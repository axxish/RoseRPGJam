#pragma once

#include "Gadget.h"
#include "SpriteSheet.h"
#include "../World/World.h"

class GameWindow : public Gadget
{
public:
    GameWindow(float normalizedWidth, float normalizedHeight, std::shared_ptr<AppConfig> appConfig);
    ~GameWindow();

    void Init() override;
    void Render(int scale) override;

    void DrawBorder(Color color, int thickness);
    void DrawSprite(const SpriteSheet &sheet, const std::string &name, int x, int y);
    void DrawSpriteGray(const SpriteSheet &sheet, const std::string &name, int x, int y);

    void BeginMode();
    void EndMode();

    void HandleInput(float deltaTime, World &world);

private:
    uint16_t p_tileSize;
    bool p_mode = false; // this bool is used to check if the renderer is in drawing mode or not

    void UpdateDimensions() override;
};