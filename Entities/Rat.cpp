#include "Rat.h"


bool Rat::DoTurn()
{
    if (!rWeCountingTime)
    {
        rWeCountingTime = true;
    }
    if (timeSinceLastMove > moveDelay)
    {
        int x = 0;
        int y = 0;

        if (rand() % 2)
        {
            x = rand() % 3;
            x -= 1;
        }
        else
        {
            y = rand() % 3;
            y -= 1;
        }

        AttemptMove(x, y);
        timeSinceLastMove = 0;
        rWeCountingTime = false;
        return true;
    }
    else
    {
        return false;
    }
}
