#pragma once

#include "Gadget.h"
#include "../Entities/Entity.h"


class EntityStatsGadget : public Gadget
{
public:
    EntityStatsGadget(float normalizedX, float normalizedY, float normalizedWidth, float normalizedHeight, std::shared_ptr<AppConfig> appConfig);
    ~EntityStatsGadget();

    void Init() override;
    void Render(int x, int y, int scale) override;

private:
    void UpdateStats(const Entity& entity);
    
};