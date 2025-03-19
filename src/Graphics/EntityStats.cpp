#include "EntityStats.h"

#include "../Entities/Entity.h"

EntityStatsGadget::EntityStatsGadget(float normalizedX, float normalizedY, float normalizedWidth,
                                     float normalizedHeight, std::shared_ptr<AppConfig> appConfig)
    : Gadget(normalizedX, normalizedY, normalizedWidth, normalizedHeight, appConfig),
      p_appConfig(appConfig)
{
    UpdateDimensions();
    p_renderTex = LoadRenderTexture(p_width, p_height);
}

EntityStatsGadget::~EntityStatsGadget()
{
    UnloadRenderTexture(p_renderTex);
}

void EntityStatsGadget::DrawStats(const Entity& entity)
{
    BeginTextureMode(p_renderTex);
    ClearBackground(BLACK);  // Clear the background to black

    int yOffset = 20;
    DrawText(entity.Name.c_str(), 20, yOffset, 20, WHITE);
    yOffset += 40;

    for (const auto& tag : entity.tags)
    {
        std::string tagText = tag.first + ": ";
        switch (tag.second.type)
        {
            case TagType::INT:
                tagText += std::to_string(tag.second.get<int>());
                break;
            case TagType::FLOAT:
                tagText += std::to_string(tag.second.get<float>());
                break;
            case TagType::BOOL:
                tagText += tag.second.get<bool>() ? "true" : "false";
                break;
            case TagType::TEXT:
                tagText += tag.second.get<std::string>();
                break;
            case TagType::CAPPED_INT:
                tagText += std::to_string(tag.second.get<CappedValue<int>>().get()) + "/" +
                           std::to_string(tag.second.get<CappedValue<int>>().getMax());
                break;
            case TagType::CAPPED_FLOAT:
                tagText += std::to_string(tag.second.get<CappedValue<float>>().get()) + "/" +
                           std::to_string(tag.second.get<CappedValue<float>>().getMax());
                break;
            default:
                tagText += "unknown";
                break;
        }
        DrawText(tagText.c_str(), 20, yOffset, 20, WHITE);
        yOffset += 40;
    }

    EndTextureMode();
}

void EntityStatsGadget::Init()
{
    p_renderTex = LoadRenderTexture(p_width, p_height);
}

void EntityStatsGadget::UpdateDimensions()
{
    p_width = static_cast<uint16_t>(GetScreenWidth() * p_normalizedWidth);
    p_height = static_cast<uint16_t>(GetScreenHeight() * p_normalizedHeight);
    p_x = static_cast<uint16_t>(GetScreenWidth() * p_normalizedX);
    p_y = static_cast<uint16_t>(GetScreenHeight() * p_normalizedY);
}

void EntityStatsGadget::OnWindowResize()
{
    UpdateDimensions();
    UnloadRenderTexture(p_renderTex);
    p_renderTex = LoadRenderTexture(p_width, p_height);
}

void EntityStatsGadget::Render(int scale)
{
    DrawTexturePro(
        p_renderTex.texture,
        {(float)0, (float)0, (float)p_renderTex.texture.width, (float)-p_renderTex.texture.height},
        {(float)p_x, (float)p_y, (float)p_renderTex.texture.width * scale,
         (float)p_renderTex.texture.height * scale},
        {0, 0}, 0, WHITE);
    DrawBorder(WHITE, 2);
}