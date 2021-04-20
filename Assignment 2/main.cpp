#include "Pacman.cpp"

int winHeight = 450;
int winWidth = 600;
string gameName = "Test";

const int fps =10;
const int frameDelay = 1000/fps;

Uint32 start;
int spend;

// Player movement
int speed = 3;

int main(int argc, char const *argv[])
{

    Pacman *game = new Pacman();
    game->init(gameName, winWidth, winHeight );

    while (game->isOn()) {
        
        start = SDL_GetTicks();

        game->eventManager(&game->event);
        game->update();
        game->render();

        spend = SDL_GetTicks() - start;

        if (frameDelay > spend) {
            SDL_Delay(frameDelay- spend);
        }
    }

    game->clean();
    return 0;
}


