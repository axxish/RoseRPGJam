#pragma once
#include "Tilemap.h"
#include <utility>

struct Room
{
    int x, y;          // Top-left corner of the room
    int width, height; // Dimensions of the room

    Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
    {
    }

    // Returns the center of the room as a pair of coordinates (useful for connecting rooms)
    std::pair<int, int> Center() const
    {
        return {x + width / 2, y + height / 2};
    }

    // Checks if this room intersects with another room
    bool Intersects(const Room &other) const
    {
        return (x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y);
    }
};

class DungeonGenerator
{
  public:
    DungeonGenerator(int width, int height) : width(width), height(height), dungeonLayout(width, height)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                dungeonLayout.SetTile(i, j, 0);
            }
        }
    }

    void Generate(int numRooms, int minRoomSize, int maxRoomSize)
    {
        std::vector<Room> rooms;

        // Step 1: Place rooms
        for (int i = 0; i < numRooms; ++i)
        {
            int roomWidth = minRoomSize + rand() % (maxRoomSize - minRoomSize + 1);
            int roomHeight = minRoomSize + rand() % (maxRoomSize - minRoomSize + 1);
            int x = rand() % (width - roomWidth - 1) + 1; // Leave a 1-tile border
            int y = rand() % (height - roomHeight - 1) + 1;

            Room newRoom(x, y, roomWidth, roomHeight);

            if (!RoomCollides(rooms, newRoom))
            {
                CreateRoomWithWalls(newRoom);
                if (!rooms.empty())
                {
                    ConnectRooms(rooms.back(), newRoom);
                }
                rooms.push_back(newRoom);
            }
        }
    }

    Tilemap GetDungeonLayout()
    {
        return dungeonLayout;
    }

    std::pair<int, int> GetRandomFloorTile() const
    {
        int x, y;
        do
        {
            x = rand() % width;
            y = rand() % height;
        } while (dungeonLayout.GetTile(x, y) != 1); // 1 is the floor tile

        return {x, y};
    }

  private:
    int width, height;
    Tilemap dungeonLayout;

    bool RoomCollides(const std::vector<Room> &rooms, const Room &newRoom)
    {
        for (const Room &room : rooms)
        {
            if (newRoom.Intersects(room))
            {
                return true;
            }
        }
        return false;
    }

    void CreateRoomWithWalls(const Room &room)
    {
        // Build walls around the room
        for (int x = room.x - 1; x <= room.x + room.width; ++x)
        {
            dungeonLayout.SetTile(x, room.y - 1, 2);           // Top wall
            dungeonLayout.SetTile(x, room.y + room.height, 2); // Bottom wall
        }
        for (int y = room.y - 1; y <= room.y + room.height; ++y)
        {
            dungeonLayout.SetTile(room.x - 1, y, 2);          // Left wall
            dungeonLayout.SetTile(room.x + room.width, y, 2); // Right wall
        }

        // Carve out floor inside the room boundaries
        for (int x = room.x; x < room.x + room.width; ++x)
        {
            for (int y = room.y; y < room.y + room.height; ++y)
            {
                dungeonLayout.SetTile(x, y, 1); // Floor tile
            }
        }
    }

    void ConnectRooms(const Room &room1, const Room &room2)
    {
        auto [x1, y1] = room1.Center();
        auto [x2, y2] = room2.Center();

        if (rand() % 2 == 0)
        {
            // Horizontal first
            CreateHorizontalCorridor(x1, x2, y1);
            CreateVerticalCorridor(y1, y2, x2);
        }
        else
        {
            // Vertical first
            CreateVerticalCorridor(y1, y2, x1);
            CreateHorizontalCorridor(x1, x2, y2);
        }
    }

    void CreateHorizontalCorridor(int x1, int x2, int y)
    {
        int minX = std::min(x1, x2);
        int maxX = std::max(x1, x2);

        for (int x = minX; x <= maxX; ++x)
        {
            dungeonLayout.SetTile(x, y, 1); // Set corridor floor tile

            // Place walls only if the tile is empty (0) and not part of a room
            if (y > 0 && dungeonLayout.GetTile(x, y - 1) == 0)
            {
                dungeonLayout.SetTile(x, y - 1, 2); // Wall above
            }
            if (y < height - 1 && dungeonLayout.GetTile(x, y + 1) == 0)
            {
                dungeonLayout.SetTile(x, y + 1, 2); // Wall below
            }
        }

        // End walls on the left and right of the corridor if they are empty
        if (minX > 0 && dungeonLayout.GetTile(minX - 1, y) == 0)
        {
            dungeonLayout.SetTile(minX - 1, y, 2); // Left wall
        }
        if (maxX < width - 1 && dungeonLayout.GetTile(maxX + 1, y) == 0)
        {
            dungeonLayout.SetTile(maxX + 1, y, 2); // Right wall
        }
    }

    void CreateVerticalCorridor(int y1, int y2, int x)
    {
        int minY = std::min(y1, y2);
        int maxY = std::max(y1, y2);

        for (int y = minY; y <= maxY; ++y)
        {
            dungeonLayout.SetTile(x, y, 1); // Set corridor floor tile

            // Place walls only if the tile is empty (0) and not part of a room
            if (x > 0 && dungeonLayout.GetTile(x - 1, y) == 0)
            {
                dungeonLayout.SetTile(x - 1, y, 2); // Wall to the left
            }
            if (x < width - 1 && dungeonLayout.GetTile(x + 1, y) == 0)
            {
                dungeonLayout.SetTile(x + 1, y, 2); // Wall to the right
            }
        }

        // End walls at the top and bottom of the corridor if they are empty
        if (minY > 0 && dungeonLayout.GetTile(x, minY - 1) == 0)
        {
            dungeonLayout.SetTile(x, minY - 1, 2); // Top wall
        }
        if (maxY < height - 1 && dungeonLayout.GetTile(x, maxY + 1) == 0)
        {
            dungeonLayout.SetTile(x, maxY + 1, 2); // Bottom wall
        }
    }
};