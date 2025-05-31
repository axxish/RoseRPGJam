# Product Requirements Document (PRD) for RoseRPG Engine

## Overview
The RoseRPG Engine is a C++-based game engine designed to drive the procedural generation, campaign loading, and gameplay mechanics of the RoseRPG roguelike game. The engine integrates with campaigns defined in YAML and INI formats and provides core gameplay features such as movement, inventory management, and combat.

---

| **ID**           | **Category**       | **Description**                                                                                     | **Details**                                                                                     |
|-------------------|--------------------|-----------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------|
| ENGINE-001        | Campaign Loading   | The engine must load campaign configurations from YAML and INI files.                              | Campaigns must include metadata, levels, rooms, structures, entities, and items.               |
| ENGINE-001-01     | Campaign Loading   | The engine must parse INI files for general campaign metadata.                                      | Metadata includes name, author, description, version, starting map, and player definition.     |
| ENGINE-001-02     | Campaign Loading   | The engine must parse YAML files for detailed campaign data.                                        | YAML files include entities, items, tiles, levels, rooms, and progression.                     |
| ENGINE-002        | Procedural Generation | The engine must support procedural generation of levels and rooms.                                 | Procedural generation must use parameters like size, density, and tile types.                  |
| ENGINE-002-01     | Procedural Generation | The engine must generate levels based on progression rules.                                         | Progression rules define level types for specific dungeon depth ranges.                        |
| ENGINE-002-02     | Procedural Generation | The engine must generate rooms with specified entities and items.                                  | Entities and items must spawn with defined probabilities.                                       |
| ENGINE-003        | Gameplay Mechanics | The engine must implement core gameplay mechanics.                                                  | Mechanics include movement, inventory management, combat, and leveling.                        |
| ENGINE-003-01     | Gameplay Mechanics | The engine must support player movement using WASD keys.                                            | Movement must interact with tiles and entities.                                                |
| ENGINE-003-02     | Gameplay Mechanics | The engine must support inventory management.                                                       | Players must be able to pick up, equip, and use items.                                          |
| ENGINE-003-03     | Gameplay Mechanics | The engine must implement combat mechanics.                                                         | Combat must calculate damage, apply effects, and update health.                                |
| ENGINE-003-04     | Gameplay Mechanics | The engine must implement leveling mechanics.                                                       | Leveling must use XP and update stats accordingly.                                              |
| ENGINE-004        | Graphics Rendering | The engine must render graphics using raylib.                                                       | Graphics include entities, tiles, and UI elements.                                              |
| ENGINE-004-01     | Graphics Rendering | The engine must load sprites from defined spritesheets.                                              | Spritesheets must be referenced in YAML files.                                                  |
| ENGINE-004-02     | Graphics Rendering | The engine must render tiles, entities, and items on the game map.                                  | Rendering must use coordinates and sizes defined in YAML files.                                 |
| ENGINE-005        | Input Handling     | The engine must handle player input for gameplay actions.                                           | Input includes movement, inventory, and interaction keys.                                       |
| ENGINE-006        | Save/Load System   | The engine must support saving and loading game states.                                             | Game states include player progress, inventory, and current level.                              |
| ENGINE-007        | Error Handling     | The engine must handle errors gracefully.                                                           | Errors include missing files, invalid configurations, and runtime exceptions.                   |

---

## Additional Notes
- The engine must be modular to allow easy integration of new campaigns.
- The engine must be optimized for performance to handle large procedural levels.
- The engine must include unit tests for core functionalities.
