#include "Application.h"
#include "Events/EventManager.h"
#include <random>


int main()
{
    srand(time(0));
    
    Application app;
    app.Run();
    return 0;
}
