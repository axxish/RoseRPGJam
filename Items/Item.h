#pragma once
#include <string>


struct Item{
    std::string Name;
    std::string SpriteName;
    float Vigour;
    float Wrath;
    float Insight;

    Item(const std::string& name, const std::string& spriteName, float vigour, float wrath, float insight) : 
    Name(name), SpriteName(spriteName), Vigour(vigour), Wrath(wrath), Insight(insight) {

    }
};

struct LootDrop{
    Item item;
    int X;
    int Y;
};