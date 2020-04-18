#include <iostream>
#include "./Constants.h"
#include "./Game.h"


#include <windows.h>
#include <string>
#include <iostream>
using namespace std;;

int main(int argc, char *argv[]) {
    Game *game = new Game();

    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->IsRunning()) {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();

    return 0;
}
