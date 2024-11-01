
#pragma once
#include "../Graphics/SpriteSheet.h"
class World;

struct Entity
{
    Entity(const std::string& name,const std::string& spriteName, int hp, int x, int y, World* worldRef);
    void DoTurn(){

    }

    bool IsOccupied(int x, int y);


    void Move(int dx, int dy);

    std::string Name;
    std::string SpriteName;
    int Hp;

    int X;
    int Y;
    World* WorldRef;
};


/*struct Player : public Entity
{
    Player(const std::string& name, const std::string& spriteName, int hp, int x, int y)
        : Entity(name, spriteName, hp, x, y) {}

    void DoTurn() override
    {
        // Handle player input or turn-based actions here
    }
};

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
