#include "Entity.h"
#include "../World/World.h"
#include <iostream>
#include <random>
Entity::Entity(const std::string &name, const std::string &spriteName, int hp, int x, int y, World *worldRef)
{
    Name = name;
    SpriteName = spriteName;
    X = x;
    Y = y;
    Hp = hp;
    WorldRef = worldRef;
}

void Entity::Move(int dx, int dy)
{
    auto tileset = WorldRef->GetTileSet()->getTileTypes();
    auto tilemap = WorldRef->GetTilemap();
    int newX = X + dx;
    int newY = Y + dy;

    if (newX >= WorldRef->GetWidth() || newY >= WorldRef->GetHeight() || newX < 0 || newY < 0)
    {
        return;
    }

    int newTile = tilemap->tiles[newY * WorldRef->GetWidth() + newX];

    if (tileset[newTile].isSolid())
    {
        return;
    }

    if (IsOccupied(newX, newY))
    {
        return;
    }

    X = newX;
    Y = newY;
}

bool Entity::IsOccupied(int x, int y)
{

    for (const Entity *entity : WorldRef->Entities)
    {
        // std::cout << entity->Name << " " << entity->X << " " << entity->Y << "\n";

        if (entity->X == x && entity->Y == y)
            return true; // Tile is occupied
    }
    return false;
}

bool Player::DoTurn()
{
    // std::cout << "player's turn";

    std::vector<Entity *> &Entities = WorldRef->Entities;
    Camera2D *Camera = &WorldRef->Camera;

    if (IsKeyPressed(KEY_W))
    {
        Move(0, -1);
        WorldRef->Camera.target = {(float)X * 16 * 3 , (float)Y * 16 * 3};
        return true;
    }
    if (IsKeyPressed(KEY_S))
    {
        Move(0, 1);
        Camera->target = {(float)X * 16 * 3, (float)Y * 16 * 3};
        return true;
    }

    if (IsKeyPressed(KEY_A))
    {
        Move(-1, 0);
        Camera->target = {(float)X * 16 * 3, (float)Y * 16 * 3};
        return true;
    }
    if (IsKeyPressed(KEY_D))
    {
        Move(1, 0);
        Camera->target = {(float)X * 16 * 3, (float)Y * 16 * 3};
        return true;
    }

    return false;
    // Handle player input or turn-based actions here
}

void Rat::OnUpdate(float deltaTime)
{
    if (rWeCountingTime)
    {
        timeSinceLastMove += deltaTime;
    }
}

bool Rat::DoTurn()
{
    if (!rWeCountingTime)
    {
        rWeCountingTime = true;
    }
    if (timeSinceLastMove > moveDelay)
    {
        int x = 0;
        int y = 0;

        if (rand() % 2)
        {
            x = rand() % 3;
            x -= 1;
        }
        else
        {
            y = rand() % 3;
            y -= 1;
        }

        Move(x, y);
        timeSinceLastMove = 0;
        rWeCountingTime = false;
        return true;
    }
    else
    {
        return false;
    }
}