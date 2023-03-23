
#include "../GameMode/Game.h"
#include <time.h>

#undef main

int main(int argc, char* argv[])
{
    srand((unsigned)time(nullptr));

    Game game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();

    return 0;
}