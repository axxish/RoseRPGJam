#include "SpriteManager.hpp"

#include <iostream>
#include <ostream>
#include <filesystem>

#include "yaml-cpp/yaml.h"
#include "Log.h"
void SpriteManager::loadFromYaml(const std::string &fileName)
{
    YAML::Node root = YAML::LoadFile(fileName);

    namespace fs = std::filesystem;

    std::string fileFormat =  ".png";
    std::string graphicsPath = ".png";

    const YAML::Node& spritesheetsNode = root["spritesheets"];
    for (const auto& it : spritesheetsNode) {
        auto sheetName = it.first.as<std::string>();
        if(!it.second["resolution"].IsDefined())
        {
            std::string errMsg;
            errMsg = "Resolution missing for spritesheet: " + sheetName;
            Log::ErrorMessage(errMsg);
            break;
        }
        auto resolution = it.second["resolution"].as<int>();
        fs::path spritesheetPath = fs::path(fileName).parent_path();

        p_atlasTextures[sheetName] = AtlasTexture(spritesheetPath.string() + "/resources/" + sheetName + ".png", resolution);

        LogInfo(sheetName + " " + std::to_string(resolution) + " " +std::to_string(p_atlasTextures[sheetName].getResolution()) + "\n");
    }

    const YAML::Node& graphicNode = root["graphics"];
    for (const auto& it : graphicNode)
    {
        auto sheetName = it.first.as<std::string>();
        if (auto atlas = p_atlasTextures.find(sheetName); atlas == p_atlasTextures.end())
        {
            LogError("No such texture found: " + sheetName);
            break;
        }

        for(const auto& spriteIt : it.second)
        {
            auto spriteName = spriteIt.first.as<std::string>();
            LogInfo("Loading texture: " + spriteName + " from atlas sheet " + sheetName);

            auto spriteValues = spriteIt.second;
            auto sprPos = spriteValues["pos"];
            std::string msg = "Texture coordinates: " + std::to_string(sprPos[0].as<int>()) + " " + std::to_string(sprPos[1].as<int>());
            LogInfo(msg);
            //TODO: parse size from yaml
            int res = p_atlasTextures[sheetName].getResolution();
            float textureSize = 1.0 * res;
            LogInfo("atlasSize: " + std::to_string(p_atlasTextures[sheetName].getResolution()));
            LogInfo("atlasTextureID: " + std::to_string(p_atlasTextures[sheetName].get().id) + "\n");
            Vector2 spriteSize = {textureSize , textureSize};
            Rectangle spriteDimensions = {(sprPos[0].as<float>()-1)*res, (sprPos[1].as<float>()-1)*res, spriteSize.x, spriteSize.y };
            auto texture = &p_atlasTextures[sheetName].get();
            p_spriteDefinitions[spriteName] = SpriteDefinition{texture, {spriteDimensions} };
        }

    }

}

std::optional<SpriteDefinition> SpriteManager::getSpriteDefinition(const std::string& name) const
{
    if (const auto element = p_spriteDefinitions.find(name); element != p_spriteDefinitions.end())
    {
        return element->second;
    }
    else
    {
        return std::nullopt;
    }
}


void SpriteManager::debugDumpSpriteDefinitions() const
{
    for (const auto& it : p_spriteDefinitions)
    {
        std::string msg = it.first + ": ";
        auto p = p_spriteDefinitions;

        msg += std::to_string(it.second.sourceRect.x) + " " + std::to_string(it.second.sourceRect.y) + " "
        + std::to_string(it.second.sourceRect.width) + " " + std::to_string(it.second.sourceRect.height) + "\n";
        LogInfo(msg + "\n");
    }

}

std::unordered_map<std::string, SpriteDefinition>& SpriteManager::debugGetDefinitions()
{
    return p_spriteDefinitions;
}


