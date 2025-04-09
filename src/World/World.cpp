#include "World.h"

#include <iostream>

#include "DungeonGenerator.h"

World::World() {}

void World::GenerateRat()
{
    std::pair<int, int> randi;
    randi = gen1->GetRandomFloorTile();
}

void World::Descend()
{
    Entities.erase(Entities.begin() + 1, Entities.end());
    gen1->Generate(4, 8);

    p_currentLevel = gen1->GetDungeonLayout();
    std::pair<int, int> rand;
    rand = gen1->GetRandomFloorTile();
    std::cout << rand.first << " " << rand.second << "\n";
    std::cout << Entities[0]->X << " " << Entities[0]->Y << "\n";
    Entities[0]->X = rand.first;
    Entities[0]->Y = rand.second;
    std::cout << Entities[0]->X << " " << Entities[0]->Y << "\n";
    rand = gen1->GetRandomFloorTile();
    Entities.push_back(new Door(rand.first, rand.second, this));

}

void World::Init(uint16_t worldWidth, uint16_t worldHeight, std::shared_ptr<TileSet> worldTileSet,
                 std::shared_ptr<SpriteSheet> spriteSheet)
{
    p_width = worldWidth;
    p_height = worldHeight;
    depth = 0;
    p_worldTileSet = worldTileSet;
    p_spriteSheet = spriteSheet;

    gen1 = std::make_shared<DungeonGenerator>(worldHeight, worldWidth);
    gen1->Generate(4, 8);
    std::pair<int, int> rand;

    p_currentLevel = gen1->GetDungeonLayout();
    rand = gen1->GetRandomFloorTile();

    Entities.push_back(new Player("player", rand.first, rand.second, this));
    EventManager::Instance().Subscribe(
        EventType::PlayerMove, [this](std::shared_ptr<Event>) { this->OnMoveCameraToPlayer(); });

    Descend();
}

void World::OnMoveCameraToPlayer()
{
    Camera.target.x = Entities[0]->X * 16;
    Camera.target.y = Entities[0]->Y * 16;
}

void World::OnDescend()
{
    OnMoveCameraToPlayer();
}

void World::AddLootDrop(Item item, int x, int y)
{
   
}

std::shared_ptr<TileSet> World::GetTileSet()
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
        renderer.DrawSprite(*p_worldTileSet->getSpriteSheet(), types[tiles[i]].getTextureName(), x,
                            y);
    }
}

void World::DrawDeadEntities(GameWindow &renderer)
{
    for (int z = 1; z < Entities.size(); z++)
    {
        auto i = Entities[z];
        if (i->isDead == true)
        {
            renderer.DrawSpriteGray(*p_spriteSheet, i->SpriteName, i->X, i->Y);
        }
    }
}

void World::DrawAliveEntities(GameWindow &renderer)
{
    for (int z = 1; z < Entities.size(); z++)
    {
        auto i = Entities[z];
        if (i->isDead == true)
        {
            // renderer.DrawSpriteGray(*p_entSpriteSheet, i->SpriteName, i->X, i->Y);
        }
        else
        {
            renderer.DrawSprite(*p_spriteSheet, i->SpriteName, i->X, i->Y);
        }
    }

    auto player = Entities[0];

    renderer.DrawSprite(*p_spriteSheet, player->SpriteName, player->X, player->Y);

    for (int z = 1; z < Entities.size(); z++)
    {
        auto i = Entities[z];
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
        StartTurn();  // Cycle back to the beginning of the turn
}

void World::OnRender(GameWindow &renderer)
{
    DrawTilemap(renderer);
    DrawDeadEntities(renderer);
    /*for (auto drop : Drops)
    {
        renderer.DrawSprite(*p_spriteSheet, drop.item.SpriteName, drop.X, drop.Y);
    }*/
    DrawAliveEntities(renderer);
}

void World::OnUpdate(float deltaTime)
{
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
