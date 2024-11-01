#pragma once
#include "../Entities/Entity.h"
#include "../Graphics/GameWindow.h"
#include "Tilemap.h"
#include "Tileset.h"

class World
{
  public:
    World();
    void OnUpdate();
    void OnRender(GameWindow &renderer);

    void DrawTilemap(GameWindow &renderer);
    TileSet *GetTileSet();
    Tilemap *GetTilemap();

    void DrawEntities(GameWindow &renderer);

    void Init(uint16_t tileSize, uint16_t worldWidth, uint16_t worldHeight);

    std::vector<Entity> Entities;

		uint16_t GetWidth(){
			return p_width;
		}

		uint16_t GetHeight(){
			return p_height;
		}

	Camera2D Camera;

  private:
    uint16_t p_width;
    uint16_t p_height;
    Tilemap p_currentLevel;
    TileSet p_worldTileSet;
    SpriteSheet *p_entSpriteSheet;

    std::vector<uint16_t> testWorld = {
        2, 2, 2, 2, 2, 0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1,

        2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0,
    };
};