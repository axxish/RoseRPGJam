#pragma once
#include <string>


struct Item{
    std::string Name;
    std::string SpriteName;
    int hp;
    int dmg;

    Item(const std::string& name, const std::string& spriteName, int hp, int dmg) : Name(name), SpriteName(name) {

    }
};

struct LootDrop{
    Item item;
    int X;
    int Y;
};