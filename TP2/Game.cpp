#include "Game.h"

#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

using namespace std;
using namespace Core;

Game::Game() : _keepPlaying(true) {}

Game::~Game() {}

/*
* 
* Main game Loop
* --------------
* Referecne: http://gameprogrammingpatterns.com/game-loop.html
*/
void Game::loop()
{
    while (_keepPlaying) 
    {
        // -- Events --
        handleInput();

        // -- Update --
        update();

        // -- draw --
        render();
    }
}
