#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "raylib.h"
#include "SpriteManager.hpp"
#include "QueueRenderer.h"
#include "Log.h"


int main()
{
    // Initialize the window
    InitWindow(800, 600, "Raylib Window");

    // Set the target FPS
    SetTargetFPS(60);


    SpriteManager spriteManager;

    const std::string campaignPath = "campaigns/Crystal Mountain";
    namespace fs = std::filesystem;

    try
    {
        if (YAML::Node config = YAML::LoadFile(campaignPath + "/general.yaml"); config["Campaign"])
        {
            const auto campaignName = config["Campaign"]["Name"].as<std::string>();
            std::cout << "Campaign Name: " << campaignName << std::endl;
        }
        else
        {
            std::cerr << "No Campaign section found in the YAML file." << std::endl;
            return 1;  // Exit with error code
        }

       
         // Load the graphics configuration
        const std::string graphicsFile(campaignPath + "/graphics.yaml");
        std::cout << "Loading graphics configuration from: " << graphicsFile << std::endl;
        spriteManager.loadFromYaml(graphicsFile);


    }
    catch (const YAML::Exception& e)
    {
        std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        return 1;  // Exit with error code
    }
    //spriteManager.debugDumpSpriteDefinitions();
    // Main game loop

    QueueRenderer Renderer(spriteManager);

    auto a = spriteManager.debugGetDefinitions();
    //auto a = spriteManager.getSpriteDefinition("wall_tile1");
    //LogInfo(std::to_string(a.value().sourceRect.x) + " " + std::to_string(a.value().sourceRect.y) + " ");


    while (!WindowShouldClose())
    {
        // Update logic here

        // Begin drawing
        BeginDrawing();
        ClearBackground(BLACK);


        Renderer.begin();
        float x = 0, y = 0;

        for (auto it : a)
        {
            Renderer.queue(RenderTargetID::Screen, it.first, 0, {x, y});
            x+=it.second.sourceRect.width;
            y+=it.second.sourceRect.height;
        }

        //Renderer.queue(RenderTargetID::Screen, "player_male", 1, {0, 0}, WHITE, 0, 6);

        Renderer.end(RenderTargetID::Screen);

        // Draw something
        DrawText("Hello, Raylib!", 350, 280, 20, DARKGRAY);

        // End drawing
        EndDrawing();
    }

    // Close the window and clean up resources
    CloseWindow();

    return 0;
}