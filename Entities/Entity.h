
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
        return true;
    }
    virtual void OnUpdate(float deltaTime);

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

    bool AddItem(const Item &item);
    void RemoveItem(int num);
    void DropItem(int num);
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
    bool isDoor = false;
    bool isPlayer = false;
    bool isHeal = false;

    bool turnSkip = false;

    float moveDelay = 0;       // The delay in seconds between AI moves
    float timeSinceLastMove = 0; // Accumulated time since the last move
    bool rWeCountingTime = false;
    World *WorldRef;
};

struct Player : public Entity
{
    Player(const std::string &name, int x, int y, World *worldRef) : Entity(name, "hero", 4, 5, 3, x, y, worldRef)
    {
        isPlayer = true;
    }

    bool DoTurn() override;

    void OnUpdate(float deltaTime) override;
};

struct Door : public Entity
{
    Door(int x, int y, World *worldRef) : Entity("Door", "door", 4, 5, 3, x, y, worldRef)
    {
        isMob = false;
        isSolid = false;
        isDead = false;
        isDoor = true;
    }
};

struct Heal : public Entity
{
    Heal(int x, int y, World *worldRef) : Entity("heal", "heal", 4, 5, 3, x, y, worldRef)
    {
        isMob = false;
        isSolid = false;
        isDead = false;
        isDoor = false;
        isHeal = true;
    }
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
