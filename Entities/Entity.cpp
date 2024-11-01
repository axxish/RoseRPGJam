#include "Entity.h"
#include "../World/World.h"
#include <iostream>
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

    if(newX >= WorldRef->GetWidth() || newY >= WorldRef->GetHeight() || newX < 0 || newY < 0){
        return;
    }

    int newTile = tilemap->tiles[newY * WorldRef->GetWidth() + newX];

    if (tileset[newTile].isSolid())
    {
        return;
    }

    if(IsOccupied(newX, newY)){
        return;
    }

    X = newX;
    Y = newY;
}

bool Entity::IsOccupied(int x, int y){
    
    for (const Entity entity : WorldRef->Entities)
    {
        std::cout << entity.Name << " " << entity.X << " " << entity.Y << "\n";

        if (entity.X == x && entity.Y == y)
            return true; // Tile is occupied
    }
    return false;

}