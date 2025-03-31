#pragma once

#include "Gadget.h"
#include "SpriteSheet.h"
#include "../World/World.h"

class GameWindow : public Gadget
{
public:
    GameWindow(float normalizedWidth, float normalizedHeight, std::shared_ptr<AppConfig> appConfig);

    void Init() override;
    void Render(int scale) override;

    void DrawBorder(Color color, int thickness);
    void DrawTileHighlight(int tileX, int tileY, Color color, const World& world) const;
    void DrawSprite(const SpriteSheet &sheet, const std::string &name, int x, int y);
    void DrawSpriteGray(const SpriteSheet &sheet, const std::string &name, int x, int y);
    Vector2 GetMouseTilePosition(const World &world) const;
    void BeginMode();
    void EndMode();

    void HandleInput(float deltaTime, World &world);

private:
    uint16_t p_tileSize;
    bool p_mode = false; // this bool is used to check if the renderer is in drawing mode or not
    std::shared_ptr<World> p_world;
    void UpdateDimensions() override;
};