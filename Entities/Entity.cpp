#include "Entity.h"
#include "../World/World.h"
#include <iostream>
#include <random>
Entity::Entity(const std::string &name, const std::string &spriteName, int vigour, int wrath, int insight, int x, int y,
               World *worldRef)
    : Vigour(vigour), Wrath(wrath), Insight(insight)
{
    Name = name;
    SpriteName = spriteName;
    X = x;
    Y = y;
    WorldRef = worldRef;
    CalculateDerivedStats();
    CurrentHP = MaxHP;
}

void Entity::CalculateDerivedStats()
{
    MaxHP = Vigour * 10;
    
    Damage = Wrath * 2;
    MaxMana = Insight * 5;
}

void Entity::GainXP(int amount)
{
    Xp += amount;
    while (Xp >= GetXPForNextLevel())
    {
        LvlUp();
    }
}

void Entity::LvlUp()
{
    int oldMaxHP = MaxHP;

    Lvl++;
    Vigour++; // Example level-up bonuses
    Wrath++;
    Insight++;
    CalculateDerivedStats(); // Recalculate derived stats after leveling up

    // Adjust current health/mana proportionally to the new max values
    CurrentHP = std::min(MaxHP, CurrentHP * MaxHP / oldMaxHP);
    CurrentMana = std::min(MaxMana, CurrentMana * MaxMana / (MaxMana - Insight * 5));
}

int Entity::GetXPForNextLevel() const
{
    return Lvl * 100;
}

Entity *Entity::IsOccupied(int x, int y)
{

    for (Entity *entity : WorldRef->Entities)
    {
        // std::cout << entity->Name << " " << entity->X << " " << entity->Y << "\n";

        if (entity->X == x && entity->Y == y)
            return entity; // Tile is occupied
    }
    return nullptr;
}

void Entity::Move(int x, int y)
{

    X = x;
    Y = y;
}

void Entity::Attack(Entity *target)
{
    target->ReceiveDamage(Damage);
}

void Entity::ReceiveDamage(int dmg)
{
    CurrentHP -= dmg;
    if (CurrentHP <= 0)
    {
        Die();
    }
}

void Entity::AttemptMove(int dx, int dy)
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

    Entity *possibleOccupant = IsOccupied(newX, newY);
    // if there's someone on the tile
    if (possibleOccupant != nullptr)
    {
        if (possibleOccupant == this)
        {
            Move(newX, newY);
            return;
        }
        if (possibleOccupant->isSolid == false)
        {
            Move(newX, newY);
        }
        if (possibleOccupant->isMob == true)
        {
            Attack(possibleOccupant);
            return;
        }
        return;
    }

    Move(newX, newY);
}

void Entity::Die()
{
    isMob = false;
    isDead = true;
    isSolid = false;
}

bool Player::DoTurn()
{
    // std::cout << "player's turn";

    std::vector<Entity *> &Entities = WorldRef->Entities;
    Camera2D *Camera = &WorldRef->Camera;
    auto i = std::make_shared<PlayerMovedEvent>();

    if (IsKeyPressed(KEY_W))
    {
        AttemptMove(0, -1);
        // WorldRef->Camera.target = {(float)X * 16 * 3, (float)Y * 16 * 3};

        EventManager::Instance().Publish(i);
        return true;
    }
    if (IsKeyPressed(KEY_S))
    {
        AttemptMove(0, 1);
        // Camera->target = {(float)X * 16 * 3, (float)Y * 16 * 3};
        EventManager::Instance().Publish(i);

        return true;
    }

    if (IsKeyPressed(KEY_A))
    {
        AttemptMove(-1, 0);
        // Camera->target = {(float)X * 16 * 3, (float)Y * 16 * 3};
        EventManager::Instance().Publish(i);

        return true;
    }
    if (IsKeyPressed(KEY_D))
    {
        AttemptMove(1, 0);
        // Camera->target = {(float)X * 16 * 3, (float)Y * 16 * 3};
        EventManager::Instance().Publish(i);
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

        AttemptMove(x, y);
        timeSinceLastMove = 0;
        rWeCountingTime = false;
        return true;
    }
    else
    {
        return false;
    }
}