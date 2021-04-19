#include "Game.cpp"
#include "Enemy.cpp"


class Pacman: public Game{
    private:
    Player *Thanos;

    Enemy *Blinky;
    Enemy *Pinky;
    Enemy *Inky ;
    Enemy *Clyde;

    TextureSet *TextureManager = new TextureSet("path of folder");
    Map *map = new Map("path of map file");

    public:

    SDL_Event event;

    void render(){
        SDL_RenderClear(renderer);
        // doBetween;
        SDL_RenderPresent(renderer);
    }

    void clean() {
        Game::clean();
        TextureManager->Free();
    }

};