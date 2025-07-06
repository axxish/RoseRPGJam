//
// Created by axxy on 04.07.2025.
//

#include "QueueRenderer.h"

#include <algorithm>

#include "Log.h"

QueueRenderer::QueueRenderer(SpriteManager& spriteMgr) : p_spriteMgr(spriteMgr) {}

void QueueRenderer::begin()
{
    // Clear the command list for every queue we have.
    for (auto& [fst, snd] : p_renderQueue)
    {
        snd.clear();
    }
}

void QueueRenderer::queue(const RenderTargetID target, const std::string& spriteName, int z_index,
                          const Vector2 position, const Color tint, const float rotation,
                          const float scale,
                          const Vector2 origin)
{
    const std::optional<SpriteDefinition> sprite = p_spriteMgr.getSpriteDefinition(spriteName);
    if (!sprite)
    {
        LogError("QueueRenderer couldn't find definition for " + spriteName);
        return;
    }

    const auto [texture, sourceRect] = sprite.value();
    const Rectangle destRect = {position.x, position.y, sourceRect.width * scale,
                          sourceRect.height * scale};
    p_renderQueue[target].push_back(
            {z_index, texture, sourceRect, destRect, origin, rotation, tint});
}

void QueueRenderer::queue(const RenderTargetID target, const RenderCommand& command)
{
    p_renderQueue[target].push_back(command);
}

void QueueRenderer::end(const RenderTargetID target)
{
    if (p_renderQueue.find(target) == p_renderQueue.end() || p_renderQueue[target].empty())
    {
        return;
    }

    auto& queueToFlush = p_renderQueue[target];

    std::sort(queueToFlush.begin(), queueToFlush.end(),
              [](const RenderCommand& a, const RenderCommand& b)
              {
                  if (a.z_index != b.z_index)
                  {
                      return a.z_index < b.z_index;
                  }
                  return a.texture->id < b.texture->id;
              });

    for (const auto& command : queueToFlush)
    {
        if (command.texture)
        {
            DrawTexturePro(*command.texture, command.sourceRect, command.destRect, command.origin,
                command.rotation, command.tint);
        }
    }
}
