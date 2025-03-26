cmake_minimum_required(VERSION 3.27.7)
project(RoseRPG VERSION 0.1.1 LANGUAGES C CXX)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib 5.0 QUIET)

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if(NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Manually list source files
set(SOURCES
    src/main.cpp
    src/Campaign.cpp
    src/Graphics/EntityStats.cpp
    src/Graphics/Gadget.cpp
    src/Graphics/SpriteSheet.cpp
    src/Graphics/GameWindow.cpp
    src/Entities/Entity.cpp
    src/Entities/Tag.cpp
    
    src/World/Tilemap.cpp
    src/World/TileSet.cpp
    src/World/World.cpp
    
    src/Events/EventManager.cpp
    src/Items/Item.cpp
    src/Util/Random.cpp
)

# Manually list header files
set(HEADERS
    src/Campaign.h
    src/Graphics/Gadget.h
    src/Graphics/GameWindow.h
    src/Graphics/SpriteSheet.h
    src/Entities/Entity.h
    src/Entities/Tag.h
    src/Events/Event.h
    src/Events/EventManager.h
    src/Items/Item.h
    src/Util/Random.h
    src/World/BSP.h
    src/World/DungeonGenerator.h
    src/World/Tilemap.h
    src/World/TileType.h
    src/World/World.h
    src/AppConfig.h
    src/Menu/Menu.h
)

add_executable(RoseRPG ${SOURCES} ${HEADERS})

target_link_libraries(RoseRPG 
    raylib
)

set_property(TARGET RoseRPG PROPERTY CXX_STANDARD 17)

target_include_directories(RoseRPG PUBLIC "${raylib_SOURCE_DIR}/src")

# Custom command to copy resources at build time
add_custom_command(
    TARGET RoseRPG POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/campaigns" "$<TARGET_FILE_DIR:RoseRPG>/campaigns"
)