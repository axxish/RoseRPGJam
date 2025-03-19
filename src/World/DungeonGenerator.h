#pragma once
#include "BSP.h"
#include "Tilemap.h"
#include <iostream>
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
    }

    void Generate(int minRoomSize, int maxRoomSize)
    {

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                dungeonLayout.SetTile(i, j, 0);
            }
        }

        Node *root = new Node(0, 0, width, height);
        std::vector<std::shared_ptr<Node>> leaves;
        root->split(minRoomSize);
        root->getLeaves(leaves);

        std::vector<Room> rooms;

        for (auto n : leaves)
        {

            int roomWidth = random(minRoomSize, std::max(minRoomSize, std::min(maxRoomSize, n->width - 2)));
            int roomHeight = random(minRoomSize, std::max(minRoomSize, std::min(maxRoomSize, n->height - 2)));

            // Ensure the room position is within valid ranges
            int roomX = n->x + random(1, std::max(1, n->width - roomWidth - 1));
            int roomY = n->y + random(1, std::max(1, n->height - roomHeight - 1));

            rooms.push_back(Room(roomX, roomY, roomWidth, roomHeight));
        }

        int i = 0;
        for (auto n : rooms)
        {
            //std::cout << i << ": " << n.x << " " << n.y << " " << n.width << " " << n.height << "\n";
            // std::cout << i;
            for (int y = n.y; y < ((n.y + n.height)); y++)
            {

                for (int x = n.x; x < (n.x + n.width); x++)
                {
                    dungeonLayout.SetTile(x, y, 1);
                }
            }
            i++;
        }
        // Connect rooms with corridors
        for (size_t i = 1; i < rooms.size(); i++)
        {
            Room &roomA = rooms[i - 1];
            Room &roomB = rooms[i];

            // Get the center points of the rooms
            int centerAx = roomA.x + roomA.width / 2;
            int centerAy = roomA.y + roomA.height / 2;
            int centerBx = roomB.x + roomB.width / 2;
            int centerBy = roomB.y + roomB.height / 2;

            // Create horizontal corridor
            for (int x = std::min(centerAx, centerBx); x <= std::max(centerAx, centerBx); x++)
            {
                dungeonLayout.SetTile(x, centerAy, 1);
            }

            // Create vertical corridor
            for (int y = std::min(centerAy, centerBy); y <= std::max(centerAy, centerBy); y++)
            {
                dungeonLayout.SetTile(centerBx, y, 1);
            }
        }

        // Place walls around the floor structures
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (dungeonLayout.GetTile(x, y) == 1)
                {
                    // Check the neighboring tiles and place walls if they are empty
                    if (dungeonLayout.GetTile(x - 1, y) == 0)
                        dungeonLayout.SetTile(x - 1, y, 2);
                    if (dungeonLayout.GetTile(x + 1, y) == 0)
                        dungeonLayout.SetTile(x + 1, y, 2);
                    if (dungeonLayout.GetTile(x, y - 1) == 0)
                        dungeonLayout.SetTile(x, y - 1, 2);
                    if (dungeonLayout.GetTile(x, y + 1) == 0)
                        dungeonLayout.SetTile(x, y + 1, 2);
                    if (dungeonLayout.GetTile(x - 1, y - 1) == 0)
                        dungeonLayout.SetTile(x - 1, y - 1, 2);
                    if (dungeonLayout.GetTile(x + 1, y - 1) == 0)
                        dungeonLayout.SetTile(x + 1, y - 1, 2);
                    if (dungeonLayout.GetTile(x - 1, y + 1) == 0)
                        dungeonLayout.SetTile(x - 1, y + 1, 2);
                    if (dungeonLayout.GetTile(x + 1, y + 1) == 0)
                        dungeonLayout.SetTile(x + 1, y + 1, 2);
                }
            }
        }
        //std::cout << dungeonLayout.getWidth() << " " << dungeonLayout.getHeight() << "\n";
        delete root;
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
};