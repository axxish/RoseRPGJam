#include "Entity.h"

#include <algorithm>
#include <iostream>
#include <random>

#include "../World/World.h"
Entity::Entity(const std::string &name, const std::string &spriteName, int vigour, int wrath,
               int x, int y, World *worldRef)
    : Vigour(vigour), Wrath(wrath)
{
    // Inventory.reserve(4);
    Name = name;
    SpriteName = spriteName;
    X = x;
    Y = y;
    WorldRef = worldRef;
    Lvl = 1;
    XP = 0;
    XpBounty = 30;
    CalculateDerivedStats();
    CurrentHP = MaxHP;

    tags["XP"] = TagValue(0);
    tags["XP"].makeDisplayable();
    tags["Lvl"] = TagValue(1);
    tags["Lvl"].makeDisplayable();
    tags["HP"] = TagValue(CappedValue(100, 100));
    tags["HP"].makeDisplayable();
    tags["AGI"] = TagValue(1);
    tags["AGI"].makeDisplayable();
    tags["STR"] = TagValue(1);
    tags["STR"].makeDisplayable();
    tags["INT"] = TagValue(1);
    tags["INT"].makeDisplayable();
}

void Entity::OnUpdate(float deltaTime)
{
    if (rWeCountingTime)
    {
        timeSinceLastMove += deltaTime;
    }
}

bool Entity::AddItem(const Item &item)
{
    /*if (Inventory.size() < inv_size)
    {
        Inventory.push_back(item);

        // Apply item's primary attribute bonuses
        Vigour += item.Vigour;
        Wrath += item.Wrath;
        Insight += item.Insight;

        // Recalculate derived stats based on updated primary attributes
        CalculateDerivedStats();
        return true;
    }*/
    return false;
}

void Entity::RemoveItem(int num)
{
    /*
    auto item = Inventory[num];
    Vigour -= item.Vigour;
    Wrath -= item.Wrath;
    Insight -= item.Insight;
    CalculateDerivedStats();

    Inventory.erase(Inventory.begin() + num);
    */
}

void Entity::DropItem(int num)
{
    /*
    if(num >= Inventory.size() ) return;
    WorldRef->AddLootDrop(Inventory.at(num), X, Y);
    RemoveItem(num);
    turnSkip = true;
    */
}

void Entity::CalculateDerivedStats()
{
    int oldMaxHP = MaxHP;
    MaxHP = Vigour * 10;

    Damage = Wrath * 2;

    // Adjust current health/mana proportionally to the new max values
    CurrentHP = std::min(MaxHP, CurrentHP * MaxHP / oldMaxHP);
}
void Entity::GainXP(int amount)
{
    XP += amount;
    while (XP >= GetXPForNextLevel())
    {
        LvlUp();
    }
}

void Entity::LvlUp()
{
    Lvl++;
    Vigour++;  // Example level-up bonuses
    Wrath++;

    CalculateDerivedStats();  // Recalculate derived stats after leveling up
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
            return entity;  // Tile is occupied
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
    if (target->isDead == false)
    {
        target->ReceiveDamage(Damage);
        if (target->isDead)
        {
            std::cout << "target dead\n";
            this->GainXP(target->XpBounty);
            std::cout << this->XP << " " << this->GetXPForNextLevel();
            this->XpBounty += target->XpBounty;
        }
    }
}

void Entity::ReceiveDamage(int dmg)
{
    int CurrentHP = tags["HP"].get<CappedValue<int>>().get();
    std::cout << tags["HP"].get<CappedValue<int>>().get();
    CurrentHP -= dmg;
    tags["HP"].value = CappedValue<int>(CurrentHP, tags["HP"].get<CappedValue<int>>().getMax());
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
        if (possibleOccupant->isDoor == true && this->isPlayer == true)
        {
            Move(newX, newY);
            // WorldRef->Descend();
            return;
        }
        if (possibleOccupant->isHeal == true && !this->isDead && this->isPlayer == true)
        {
            WorldRef->Entities[0]->CurrentHP = WorldRef->Entities[0]->MaxHP;
            possibleOccupant->Die();
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
    DropItem(0);
}

bool Player::DoTurn()
{
    // std::cout << "player's turn";
    if (turnSkip)
    {
        turnSkip = false;
        return true;
    }

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
    if (IsKeyPressed(KEY_E))
    {
        /*
        for (int i = 0; i < WorldRef->Drops.size(); i++)
        {
            auto drop = WorldRef->Drops[i];
            if (drop.X == X && drop.Y == Y)
            {
                if (Inventory.size() < inv_size)
                {
                    AddItem(drop.item);

                    WorldRef->Drops.erase(WorldRef->Drops.begin() + i);
                    return true;
                }
            }
        }
        */
        for (auto entity : Entities)
        {
            if (entity->isDoor == true && entity->X == X && entity->Y == Y)
            {
                WorldRef->Descend();
                EventManager::Instance().Publish(i);
                return true;
            }
        }
        // AttemptMove(1, 0);
        //  Camera->target = {(float)X * 16 * 3, (float)Y * 16 * 3};
        // EventManager::Instance().Publish(i);
        return true;
    }

    return false;
    // Handle player input or turn-based actions here
}

void Player::OnUpdate(float deltaTime)
{
    // do nuthin
}