#include "Pacman.cpp"


int main(int argc, char const *argv[])
{

    Pacman *game = new Pacman();
    game->init();

    const int frameDelay = 1000/FPS;

    Uint32 start;
    int spend;

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


