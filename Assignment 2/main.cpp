#include "Pacman.cpp"

int winHeight = 600;
int winWidth = 500;
string gameName = "Test";

// Player movement
int speed = 3;

int main(int argc, char const *argv[])
{
    Pacman *game = new Pacman();
    game->init(gameName, winWidth, winHeight);

    while (game->isOn()) {
        game->eventManager(&game->event);
        game->render();
    }

    game->clean();
    return 0;
}


