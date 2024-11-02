#pragma once
#include "../Entities/Entity.h"
#include "../Graphics/GameWindow.h"
#include "Tilemap.h"
#include "Tileset.h"

class World
{
  public:
    World();
    void OnUpdate(float deltaTime);
    void OnRender(GameWindow &renderer);

    void DrawTilemap(GameWindow &renderer);
    TileSet *GetTileSet();
    Tilemap *GetTilemap();

    void DrawEntities(GameWindow &renderer);

    // FUCK single responsibility principle, im running out of time.
    // Originally these functions were meant to be a TurnManager class
    // but the World can manage the turns just fine for now

    void StartTurn();

    Entity *GetCurrentEntity();

    void EndTurn();

    void Init(uint16_t tileSize, uint16_t worldWidth, uint16_t worldHeight);

    uint16_t GetWidth()
    {
        return p_width;
    }

    uint16_t GetHeight()
    {
        return p_height;
    }

		bool GetIsItPlayerMove();

    std::vector<Entity*	> Entities;

    Camera2D Camera;

		

  private:
    uint16_t p_width;
    uint16_t p_height;
    Tilemap p_currentLevel;
    TileSet p_worldTileSet;
    SpriteSheet *p_entSpriteSheet;

    // this is for the turn managing
    size_t p_currentEntityIndex = 0;

    std::vector<uint16_t> testWorld = {
        2, 2, 2, 2, 2, 0, 0, 0,
				2, 1, 1, 1, 2, 0, 0, 0,
				2, 1, 1, 1, 2, 0, 0, 0,
				2, 1, 1, 1, 2, 0, 0, 0,
        2, 1, 1, 1, 2, 0, 0, 0,
				2, 1, 1, 1, 2, 0, 0, 0,
				2, 1, 1, 1, 2, 0, 0, 0,
				2, 2, 2, 2, 2, 0, 0, 0,
    };
};