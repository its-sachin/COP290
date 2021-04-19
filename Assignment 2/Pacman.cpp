#include "Game.cpp"
#include "Enemy.cpp"


class Pacman: public Game{
    private:
    Player *Thanos;

    Enemy *Blinky;
    Enemy *Pinky;
    Enemy *Inky ;
    Enemy *Clyde;

    TextureSet *textureManager = NULL;
    Map *map = NULL; 

    public:

    SDL_Event event;

    void init(string title, int width, int height) {

        const char* temp = title;
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height);
        if (isRunning) {
            TextureSet::renderer = renderer;
            textureManager = new TextureSet("path of folder");
            map = new Map("path of map file");
            map->genrateMap(textureManager);
        }

    }

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