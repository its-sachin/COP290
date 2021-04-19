#include "Pacman.cpp"

int main(int argc, char const *argv[])
{
    Pacman *game = new Pacman();
    game->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 600);

    while (game->isOn()) {
        game->eventManager();
        game->render();
    }

    game->clean();
    return 0;
}


