#include "Pacman.cpp"


int main(int argc, char const *argv[])
{

    Pacman *game = new Pacman(Single);
    game->init();

    Uint32 start;
    int spend;

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


