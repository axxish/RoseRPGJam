
#pragma once
#include "../Graphics/SpriteSheet.h"
#include "../Items/Item.h"
class World;

struct Entity
{
    

    Entity(const std::string &name, const std::string &spriteName, int vigour, int wrath, int insight, int x, int y,
           World *worldRef);
    virtual bool DoTurn()
    {
        return false;
    }
    // returns nullptr is it isnt
    Entity *IsOccupied(int x, int y);

    void CalculateDerivedStats();
    void GainXP(int amount);
    void LvlUp();

    int GetXPForNextLevel() const;
    void Move(int dx, int dy);
    void AttemptMove(int dx, int dy);
    void Attack(Entity *target);
    void ReceiveDamage(int dmg);
    void Die();

    virtual void OnUpdate(float deltaTime)
    {
    }

    bool AddItem(const Item &item);
    void RemoveItem(int num);
    /*void AddItem(const Item& item){

    }*/

    std::string Name;
    std::string SpriteName;

    std::vector<Item> Inventory;
    const static int inv_size = 4;

    int Lvl;
    int XP;
    int XpBounty;

    // attributes everything else scales off
    int Vigour;  // hp
    int Wrath;   // dmg
    int Insight; // mana and spell dmg

    int MaxHP;
    int CurrentHP;
    int Damage;
    int MaxMana;
    int CurrentMana;

    int X;
    int Y;

    bool isMob = true;
    bool isDead = false;
    bool isSolid = true;

    // std::vector<Item> Inventory;

    World *WorldRef;
};

struct Player : public Entity
{
    Player(const std::string &name, int x, int y, World *worldRef) : Entity(name, "hero", 4, 5, 3, x, y, worldRef)
    {
        
    }

    bool DoTurn() override;
};

struct Rat : public Entity
{
    Rat(const std::string &name, int x, int y, World *worldRef) : Entity(name, "rat", 2, 5, 1, x, y, worldRef)
    {
        XpBounty = 30;
    }

    float moveDelay = 0.2;       // The delay in seconds between AI moves
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
