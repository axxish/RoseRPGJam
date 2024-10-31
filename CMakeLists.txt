cmake_minimum_required(VERSION 3.27.7)
project(RoseRPG VERSION 0.1.0 LANGUAGES C CXX)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib 5.0 QUIET)

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_executable(RoseRPG main.cpp Graphics/GameWindow.cpp Graphics/SpriteSheet.cpp World/Tilemap.cpp World/TileSet.cpp Application.cpp )

target_link_libraries(RoseRPG 
    raylib
)

target_include_directories(RoseRPG PUBLIC "${raylib_SOURCE_DIR}/src")

FILE(COPY resources/creatures.png DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources")
FILE(COPY resources/maptiles.png DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources")