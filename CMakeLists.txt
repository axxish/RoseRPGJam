cmake_minimum_required(VERSION 3.27.7)
project(evermoprhing LANGUAGES C CXX)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib 5.5 QUIET)

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if(NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG        0.8.0 
)

FetchContent_MakeAvailable(yaml-cpp)


add_custom_target(copy_campaigns ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/campaigns
    $<TARGET_FILE_DIR:textureTest>/campaigns
    COMMENT "Copying campaigns folder to build directory + <TARGET_FILE_DIR:textureTest>"
)


add_executable(
    textureTest
        src/Log.cpp
        src/Log.h
        src/QueueRenderer.cpp
        src/QueueRenderer.h
        src/RenderTargetID.hpp
)

set(HEADERS
        src/AtlasTexture.hpp
    src/useful.h
    src/SpriteManager.hpp 
    )

set (SOURCES
        src/AtlasTexture.cpp
        src/SpriteManager.cpp
    src/main.cpp
)


target_sources(
    textureTest
    PUBLIC
        ${HEADERS}
    PRIVATE
        ${SOURCES}
)



target_link_libraries(
    textureTest
    PRIVATE
    raylib
    yaml-cpp
)

add_dependencies(textureTest copy_campaigns)

target_include_directories(textureTest PUBLIC "${raylib_SOURCE_DIR}/src")