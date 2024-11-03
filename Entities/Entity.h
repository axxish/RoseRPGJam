
#pragma once
#include "../Graphics/SpriteSheet.h"
class World;

struct Entity
{
    Entity(const std::string &name, const std::string &spriteName, int hp, int damage, int x, int y, World *worldRef);
    virtual bool DoTurn()
    {
        return false;
    }
    //returns nullptr is it isnt
    Entity* IsOccupied(int x, int y);

    void Move(int dx, int dy);
    void AttemptMove(int dx, int dy);
    void Attack(Entity * target);
    void ReceiveDamage(int dmg);
    void Die();

    virtual void OnUpdate(float deltaTime){
    
    }

    std::string Name;
    std::string SpriteName;

    bool isMob = true;
    bool isDead = false;
    bool isSolid = true;

    int Hp;
    int Damage;

    int X;
    int Y;

    World *WorldRef;
};

struct Player : public Entity
{
    Player(const std::string &name, int hp, int x, int y, World *worldRef) : Entity(name, "hero", hp, 10 , x, y, worldRef)
    {
    }

    bool DoTurn() override;
};

struct Rat : public Entity
{
    Rat(const std::string &name, int hp, int x, int y, World *worldRef) : Entity(name, "rat", hp, 10, x, y, worldRef)
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
