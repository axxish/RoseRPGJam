#include "../Util/Random.h"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

struct Node
{
    int x;
    int y;
    int width;
    int height;

    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;

    Node(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), left(nullptr), right(nullptr)
    {
    }

    std::pair<int, int> getCenter()
    {
        return {x + width / 2, y + height / 2};
    }

    void getLeaves(std::vector<std::shared_ptr<Node>> &leaves) const
    {
        if (!left && !right)
        {
            // This is a leaf node
            leaves.push_back(std::make_shared<Node>(*this));
        }

        else
        {
            // Recurse through left and right children
            if (left)
            {
                left->getLeaves(leaves);
            }
            if (right)
            {
                right->getLeaves(leaves);
            }
        }
    }
    void split(int minSize)
    {
        int orientation;
        int splitLocation;
        //std::cout << width << " " << height << "\n";
        if (width > height && width > minSize * 2)
        {
            orientation = 0;
        }
        else if (height > width && height > minSize * 2)
        {
            orientation = 1;
        }
        else if (width > minSize * 2 && height > minSize * 2)
        {
            orientation = random(0, 1);
        }
        else
        {
            return;
        }

        if (orientation == 0)
        {
            //std::cout << "vertical\n";
            splitLocation = random(minSize, width - minSize);
            left = std::make_shared<Node>(x, y, splitLocation, height);
            right = std::make_shared<Node>(x + splitLocation , y, width - splitLocation, height);
        }
        else
        {
            //std::cout << "horizontal\n";
            splitLocation = random(minSize, height - minSize);
            left = std::make_shared<Node>(x, y, width, splitLocation);
            right = std::make_shared<Node>(x, y + splitLocation , width, height - splitLocation );
        }

        //std::cout << "left: " << left->x << " " << left->y << " " << left->width << " " << left->height << "\n";
        //std::cout << "right: " << right->x << " " << right->y << " " << right->width << " " << right->height << "\n";
        
        if (left->width >= minSize * 2 && left->height >= minSize * 2)
        {
            left->split(minSize);
        }
        if (right->width >= minSize * 2 && right->height >= minSize * 2)
        {
            right->split(minSize);
        }
    }
};
