#pragma once
#include <raylib.h>

#include <memory>
#include <optional>
#include <unordered_map>

#include "AtlasTexture.hpp"
#include "useful.h"

struct SpriteDefinition {
    const Texture2D* texture = nullptr; // Pointer to the texture, not the texture itself
    Rectangle sourceRect = {0}; // THE RECTANGLE IS IN PIXELS
};


class SpriteManager
{
public:
    SpriteManager() = default;
    ~SpriteManager() = default;

    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;
    SpriteManager(SpriteManager&&) = delete;
    SpriteManager& operator=(SpriteManager&&) = delete;

    void loadFromYaml(const std::string& fileName);
    std::optional<SpriteDefinition> getSpriteDefinition(const std::string& name) const;

    void debugDumpSpriteDefinitions() const;

    std::unordered_map<std::string, SpriteDefinition>& debugGetDefinitions();

private:
    std::unordered_map<std::string, SpriteDefinition> p_spriteDefinitions;
    std::unordered_map<std::string, AtlasTexture> p_atlasTextures;

    Vector2 p_defaultSize = {1, 1};
};

