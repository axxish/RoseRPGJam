#pragma once
#include "Entity.h"


struct Rat : public Entity
{
    Rat( int x, int y, World *worldRef) : Entity("Rat", "rat", 2, 5, x, y, worldRef)
    {
        XpBounty = 30;
        
    }

    bool DoTurn() override;
};