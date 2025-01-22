#include "World.h"
#include "DungeonGenerator.h"
#include <iostream>

World::World()
{
}

void World::GenerateRat()
{
    std::pair<int, int> randi;
    randi = gen1->GetRandomFloorTile();
    auto rat = Rat(randi.first, randi.second, this);
    auto rand2 = rand() % 4;
    switch (rand2)
    {
    case 0:
        rat.AddItem(Item("sword", "sword", 1, 3, 0));
        break;
    case 1:
        rat.AddItem(Item("greatsword", "sword", 2, 5, 0));
        break;
    case 2:
        rat.AddItem(Item("helm", "helm", 2, 0, 0));
        break;
    case 3:
        rat.AddItem(Item("shield", "shield", 4, 1, 0));
        break;
    default:

        break;
    }
    Entities.push_back(new Rat(rat));
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

    for(int i = 0; i < 4; i++){
        GenerateRat();
    }

    rand = gen1->GetRandomFloorTile();
    Entities.push_back(new Heal(rand.first, rand.second, this));
}

void World::Init(uint16_t worldWidth, uint16_t worldHeight, TileSet *worldTileSet, std::shared_ptr<SpriteSheet> spriteSheet)
{

    p_width = worldWidth;
    p_height = worldHeight;
    depth = 0;
    p_worldTileSet = worldTileSet;
    p_spriteSheet = spriteSheet;
 
    // p_currentLevel = Tilemap(worldWidth, worldHeight);
    // p_currentLevel.tiles = testWorld;


    gen1 = std::make_shared<DungeonGenerator>(worldHeight, worldWidth);
    gen1->Generate(4, 8);
    std::pair<int, int> rand;

    p_currentLevel = gen1->GetDungeonLayout();
    rand = gen1->GetRandomFloorTile();

    Entities.push_back(new Player("player", rand.first, rand.second, this));
    EventManager::Instance().Subscribe(EventType::PlayerMove,
                                       [this](std::shared_ptr<Event>) { this->OnMoveCameraToPlayer(); });
    
   Descend();
}

void World::OnMoveCameraToPlayer()
{
    Camera.target.x = Entities[0]->X * 16 * 3;
    Camera.target.y = Entities[0]->Y * 16 * 3;
}

void World::OnDescend()
{
    OnMoveCameraToPlayer();
}


void World::AddLootDrop(Item item, int x, int y)
{

    Drops.push_back(LootDrop(item, x, y));
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
        if (i->isMob)
        {
            // DrawText(std::to_string(i->CurrentHP).c_str(), i->X * 16 * 3, i->Y * 16 * 3, 12, RED);
            float healthPercentage = static_cast<float>(i->CurrentHP) / i->MaxHP;
            int greenBarWidth = static_cast<int>(healthPercentage * (11));
            DrawRectangle((i->X * 16 * 3) + 8, (i->Y * 16 * 3) - 4, 11 * 3, 2, RED);
            DrawRectangle((i->X * 16 * 3) + 8, (i->Y * 16 * 3) - 4, greenBarWidth * 3, 2, GREEN);
            DrawText(std::to_string(i->Lvl).c_str(), (i->X * 16 * 3), (i->Y * 16 * 3) - 8, 12, YELLOW);
            DrawText(i->Name.c_str(), (i->X * 16 * 3) + 4, (i->Y * 16 * 3) - 16, 12, YELLOW);
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
    DrawDeadEntities(renderer);
    for (auto drop : Drops)
    {
        renderer.DrawSprite(*p_spriteSheet, drop.item.SpriteName, drop.X, drop.Y);
    }
    DrawAliveEntities(renderer);
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
