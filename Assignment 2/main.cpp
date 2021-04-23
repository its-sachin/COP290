#include "Pacman.cpp"


int main(int argc, char const *argv[])
{

    Pacman *game = new Pacman();

    Uint32 start;
    int spend;

    game->init();
    while (game->isOn()) {
        
        start = SDL_GetTicks();

        game->eventManager(&game->event);
        game->update();
        game->render();

        spend = SDL_GetTicks() - start;

        if (FRAME_DELAY > spend) {
            SDL_Delay(FRAME_DELAY- spend);
        }
    }

    game->clean();
    return 0;
}


