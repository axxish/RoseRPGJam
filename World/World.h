#pragma once
#include "../Entities/Entity.h"
#include "../Graphics/GameWindow.h"
#include "Tilemap.h"
#include "Tileset.h"
#include "../Events/EventManager.h"

class World
{
  public:
    World();
    ~World(){
      for(auto ent : Entities){
        delete ent;
      }
    }
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

    void Init(uint16_t worldWidth, uint16_t worldHeight, TileSet* worldTileSet, SpriteSheet* creatureSheet, SpriteSheet* itemSpriteSheet);

    uint16_t GetWidth()
    {
        return p_width;
    }

    uint16_t GetHeight()
    {
        return p_height;
    }

		bool GetIsItPlayerMove();

    void OnMoveCameraToPlayer();

    void AddLootDrop(Item item,int x, int y);


    std::vector<Entity*	> Entities; // this stores pointers to allow polymorphism for Entity inheritors
    std::vector<LootDrop> Drops;

    Camera2D Camera;

    bool isDragging = false;
    Vector2 pivotCamera;

  private:
    uint16_t p_width;
    uint16_t p_height;
    Tilemap p_currentLevel;
    
    SpriteSheet* p_entSpriteSheet;
    TileSet* p_worldTileSet;
    SpriteSheet *p_itemSpriteSheet;

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