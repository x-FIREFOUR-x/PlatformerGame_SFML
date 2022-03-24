#include "stdafx.h"
#include "Game.h"



int main()
{
    srand(time(NULL));

    Game game;
    while (game.getWindow().isOpen())
    {
        game.update();
        game.render();
    }

    return 0;
}
