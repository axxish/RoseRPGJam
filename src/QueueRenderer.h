//
// Created by axxy on 04.07.2025.
//
#pragma once
#include <vector>

#include "SpriteManager.hpp"
#include "raylib.h"
#include "RenderTargetID.hpp"
#include <map>
#pragma once
class QueueRenderer {
public:
    struct RenderCommand
    {
        int z_index = 0;
        const Texture2D* texture = nullptr;
        Rectangle sourceRect = {0, 0, 0, 0};
        Rectangle destRect = {0, 0, 0, 0};
        Vector2 origin = {0, 0};
        float rotation = 0.0f;
        Color tint = WHITE;
    };

public:
    explicit QueueRenderer(SpriteManager& spriteMgr);
    ~QueueRenderer() = default;

    QueueRenderer(const QueueRenderer& other) = delete;
    QueueRenderer& operator=(const QueueRenderer& other) = delete;

    void queue(RenderTargetID target ,const std::string& spriteName, int z_index, Vector2 position, Color tint = WHITE,
        float rotation = 0.0f, float scale = 1.0f, Vector2 origin = {0, 0});

    void queue(RenderTargetID target, const RenderCommand& command);

    void begin();
    void end(RenderTargetID target);

private:
    SpriteManager& p_spriteMgr;
    std::map<RenderTargetID, std::vector<RenderCommand>> p_renderQueue;
};
