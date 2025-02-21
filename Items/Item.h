#pragma once
#include <string>

struct Entity;

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

class ItemBehaviour{
    virtual void OnUse(Entity* entity) ;
};

class HealPotionBehaviour : public ItemBehaviour{
    int healAmount;
    HealPotionBehaviour(int healAmount) : healAmount(healAmount) {

    }
    void OnUse(Entity* entity) override;
};