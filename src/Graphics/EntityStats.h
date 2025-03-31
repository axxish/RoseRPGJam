#pragma once

#include "Gadget.h"
#include "../Entities/Entity.h"


class EntityStatsGadget : public Gadget
{
public:
    EntityStatsGadget(float normalizedX, float normalizedY, float normalizedWidth, float normalizedHeight, std::shared_ptr<AppConfig> appConfig);
    ~EntityStatsGadget();
    void DrawStats(const Entity& entity);
    void Init() override;
    void Render(int scale) override;
    void UpdateDimensions() override;
    void OnWindowResize() override;

    //void Init() override;
    //void Render(int x, int y, int scale) override;

private:
    std::shared_ptr<AppConfig> p_appConfig;
    
};