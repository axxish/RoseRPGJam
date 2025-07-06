//
// Created by axxy on 06.07.2025.
//

#pragma once

enum class RenderTargetID {
    Screen,  // The default backbuffer, for drawing directly to the window
    World,   // For all game world objects (players, enemies, scenery)
    UI      // For user interface elements
};


