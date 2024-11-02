
#pragma once
#include "../Graphics/SpriteSheet.h"
class World;

struct Entity
{
    Entity(const std::string &name, const std::string &spriteName, int hp, int x, int y, World *worldRef);
    virtual bool DoTurn()
    {
        return false;
    }

    bool IsOccupied(int x, int y);

    void Move(int dx, int dy);

    virtual void OnUpdate(float deltaTime){
    
    }

    std::string Name;
    std::string SpriteName;
    int Hp;

    int X;
    int Y;
    World *WorldRef;
};

struct Player : public Entity
{
    Player(const std::string &name, int hp, int x, int y, World *worldRef) : Entity(name, "hero", hp, x, y, worldRef)
    {
    }

    bool DoTurn() override;
};

struct Rat : public Entity
{
    Rat(const std::string &name, int hp, int x, int y, World *worldRef) : Entity(name, "rat", hp, x, y, worldRef)
    {
    }

    float moveDelay = 0.2;     // The delay in seconds between AI moves
    float timeSinceLastMove = 0; // Accumulated time since the last move
    bool rWeCountingTime = false;

    void OnUpdate(float deltaTime) override;

    bool DoTurn() override;
};
/*
struct Mob : public Entity
{
    Mob(const std::string& name, const std::string& spriteName, int hp, int x, int y)
        : Entity(name, spriteName, hp, x, y) {}

    void DoTurn() override
    {
        // Handle player input or turn-based actions here
    }
};
*/
