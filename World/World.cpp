#include "World.h"
#include <iostream>

World::World()
{
}

void World::Init(uint16_t worldWidth, uint16_t worldHeight, TileSet *worldTileSet, SpriteSheet *creatureSheet,
                 SpriteSheet *itemSpriteSheet)
{

    p_width = worldWidth;
    p_height = worldHeight;

    p_worldTileSet = worldTileSet;
    p_entSpriteSheet = creatureSheet;
    p_itemSpriteSheet = itemSpriteSheet;

    p_currentLevel = Tilemap(worldWidth, worldHeight);
    p_currentLevel.tiles = testWorld;

    Entities.push_back(new Player("player", 1, 1, this));

    Entities[0]->AddItem(Item("Basic sword", "sword", 1, 2, 0));

    Entities.push_back(new Rat("Rat", 2, 3, this));

    Entities.push_back(new Rat("Rat", 3, 4, this));

    Entities.push_back(new Rat("Rat", 3, 5, this));

    EventManager::Instance().Subscribe(EventType::PlayerMove,
                                       [this](std::shared_ptr<Event>) { this->OnMoveCameraToPlayer(); });
}

void World::OnMoveCameraToPlayer()
{
    Camera.target.x = Entities[0]->X * 16 * 3;
    Camera.target.y = Entities[0]->Y * 16 * 3;
}

TileSet *World::GetTileSet()
{
    return p_worldTileSet;
}

Tilemap *World::GetTilemap()
{
    return &p_currentLevel;
}

void World::DrawTilemap(GameWindow &renderer)
{
    std::vector<TileType> types = p_worldTileSet->getTileTypes();
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
        renderer.DrawSprite(p_worldTileSet->getSpriteSheet(), types[tiles[i]].getTextureName(), x, y);
    }
}

void World::DrawEntities(GameWindow &renderer)
{
    for (int z = 1; z < Entities.size(); z++)
    {
        auto i = Entities[z];
        if (i->isDead == true)
        {
            renderer.DrawSpriteGray(*p_entSpriteSheet, i->SpriteName, i->X, i->Y);
        }
        else
        {
            renderer.DrawSprite(*p_entSpriteSheet, i->SpriteName, i->X, i->Y);
        }
        }

    auto player = Entities[0];

    renderer.DrawSprite(*p_entSpriteSheet, player->SpriteName, player->X, player->Y);

    for (int z = 1; z < Entities.size(); z++)
    {
        auto i = Entities[z];
        if (i->isMob)
        {
            // DrawText(std::to_string(i->CurrentHP).c_str(), i->X * 16 * 3, i->Y * 16 * 3, 12, RED);
            float healthPercentage = static_cast<float>(i->CurrentHP) / i->MaxHP;
            int greenBarWidth = static_cast<int>(healthPercentage * (11));
            DrawRectangle((i->X * 16 * 3) + 8, (i->Y * 16 * 3) - 4, 11 * 3, 2, RED);
            DrawRectangle((i->X * 16 * 3) + 8, (i->Y * 16 * 3) - 4, greenBarWidth * 3, 2, GREEN);
            DrawText(std::to_string(i->Lvl).c_str(), (i->X * 16 * 3), (i->Y * 16 * 3) - 8, 12, YELLOW );
            DrawText(i->Name.c_str(), (i->X * 16 * 3) + 4, (i->Y * 16 * 3) - 16, 12, YELLOW );
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
            newX = newX;
            newY = newY;
            Camera.target.x += newX;
            Camera.target.y += newY;
            pivotCamera = GetMousePosition();
        }
        // auto delta = GetMouseDelta();
        // p_camera.target.x -= delta.x;
        // p_camera.target.y -= delta.y;
    }
    else
    {
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
        if (currentEntity->isDead == true)
        {
            EndTurn();
        }
        else if (currentEntity->DoTurn())
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