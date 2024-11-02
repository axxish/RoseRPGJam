#include "World.h"
#include <iostream>

World::World()
{
}

void World::Init(uint16_t tileSize, uint16_t worldWidth, uint16_t worldHeight)
{

    p_width = worldWidth;
    p_height = worldHeight;

    p_worldTileSet = TileSet("resources/maptiles.png", tileSize);
    p_worldTileSet.addTileType("air", {1, 7, 1, 1}, false);
    p_worldTileSet.addTileType("floor", {3, 3, 1, 1}, false);
    p_worldTileSet.addTileType("wall", {1, 1, 1, 1}, true);

    p_entSpriteSheet = new SpriteSheet("resources/creatures.png", tileSize);

    p_entSpriteSheet->AddSprite("hero", {0, 0, 1, 1});
    p_entSpriteSheet->AddSprite("rat", {1, 1, 1, 1});

    p_currentLevel = Tilemap(worldWidth, worldHeight);
    p_currentLevel.tiles = testWorld;

    Entities.push_back(new Player("player", 100, 1, 1, this));

    Entities.push_back(new Rat("Rat", 100, 2, 3, this));

    Entities.push_back(new Rat("Rat", 100, 3, 4, this));

    Entities.push_back(new Rat("Rat", 100, 3, 5, this));
}

TileSet *World::GetTileSet()
{
    return &p_worldTileSet;
}

Tilemap *World::GetTilemap()
{
    return &p_currentLevel;
}

void World::DrawTilemap(GameWindow &renderer)
{
    std::vector<TileType> types = p_worldTileSet.getTileTypes();
    std::vector<uint16_t> tiles = p_currentLevel.tiles;

    int width = p_currentLevel.getWidth();
    int height = p_currentLevel.getHeight();
    int y = 0;

    for (int i = 0, x = 0; i < tiles.size(); i++, x++)
    {
        // if the iterator is greater than the width we go to next line
        if (x >= width)
        {
            y++;
            x = 0;
        }
        renderer.DrawSprite(p_worldTileSet.getSpriteSheet(), types[tiles[i]].getTextureName(), x, y);
    }
}

void World::DrawEntities(GameWindow &renderer)
{
    for (Entity *i : Entities)
    {
        renderer.DrawSprite(*p_entSpriteSheet, i->SpriteName, i->X, i->Y);
        if(i->isMob){
            DrawText(std::to_string(i->Hp).c_str(), i->X * 16 * 3, i->Y * 16 * 3, 12, RED);
        }
    }
}

void World::StartTurn()
{
    p_currentEntityIndex = 0;
}

Entity *World::GetCurrentEntity()
{
    if (p_currentEntityIndex < Entities.size())
        return Entities[p_currentEntityIndex];
    return nullptr;
}

void World::EndTurn()
{
    p_currentEntityIndex++;
    if (p_currentEntityIndex >= Entities.size())
        StartTurn(); // Cycle back to the beginning of the turn
}

void World::OnRender(GameWindow &renderer)
{
    DrawTilemap(renderer);
    DrawEntities(renderer);
}

void World::OnUpdate(float deltaTime)
{

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        if (!isDragging)
        {
            pivotCamera = GetMousePosition();
            isDragging = true;
        }

        if (isDragging)
        {
            auto newX = pivotCamera.x - GetMousePosition().x;
            auto newY = pivotCamera.y - GetMousePosition().y;
            newX = newX ;
            newY = newY ;
            Camera.target.x += newX;
            Camera.target.y += newY;
            pivotCamera = GetMousePosition();
        }
        // auto delta = GetMouseDelta();
        // p_camera.target.x -= delta.x;
        // p_camera.target.y -= delta.y;
    }else{
        isDragging = false;
    }

    

    for (Entity *e : Entities)
    {
        e->OnUpdate(deltaTime);
    }

    Entity *currentEntity = GetCurrentEntity();

    // std::cout << currentEntity->Name << " ";
    if (currentEntity)
    {
        if (currentEntity->DoTurn())
        {
            EndTurn();
        }
    }
}

bool World::GetIsItPlayerMove()
{
    if (p_currentEntityIndex == 0)
    {
        return true;
    }
    return false;
}