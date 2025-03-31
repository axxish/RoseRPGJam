#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "Campaign.h"
#include "raylib.h"

namespace fs = std::filesystem;

int main()
{
    // Initialize window
    InitWindow(800, 600, "Select Campaign");
    SetTargetFPS(144);
    SetExitKey(0);

    // Read campaign folders
    std::vector<std::string> campaigns;
    std::string campaignsPath = "campaigns";

    try
    {
        for (const auto& entry : fs::directory_iterator(campaignsPath))
        {
            if (entry.is_directory())
            {
                campaigns.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        std::cerr << "Could not open campaigns directory: " << e.what() << std::endl;
        return 1;
    }

    int selected = 0;
    bool running = true;

    while (!WindowShouldClose() && running)
    {
        // Handle input
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            selected = (selected + 1) % campaigns.size();
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            selected = (selected - 1 + campaigns.size()) % campaigns.size();
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            running = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw campaign list
        for (int i = 0; i < campaigns.size(); i++)
        {
            if (i == selected)
            {
                DrawText(("> " + campaigns[i]).c_str(), 100, 100 + i * 20, 20, YELLOW);
            }
            else
            {
                DrawText(campaigns[i].c_str(), 100, 100 + i * 20, 20, WHITE);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    // Save selected campaign path
    std::string selectedCampaignPath = campaignsPath + "/" + campaigns[selected];
    std::cout << "Selected campaign: " << selectedCampaignPath << std::endl;
    Campaign app;
    app.Run(selectedCampaignPath);

    return 0;
}