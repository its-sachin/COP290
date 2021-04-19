#include "Game.cpp"
#include "Player.cpp"
#include "Enemy.cpp"
#include "Map.cpp"


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