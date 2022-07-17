#include "maze.h"
#include "game.h"
#include <string.h>
#include <map>

using namespace std;
int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init game engine

    Game game;

    //Game loop
    while(game.running()){

        //Update
        game.update();

        //Render
        game.render();
    }

    return 0;
}

