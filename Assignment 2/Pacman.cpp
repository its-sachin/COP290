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

        const char* temp = title.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height);
        if (isRunning) {
            textureManager = new TextureSet("Assets/Images", renderer);
            map = new Map("Assets/Maps/map1.txt");
            map->genrateMap(textureManager);
        }

    }

    void render(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        textureManager->getTexture("bg")->Draw(renderer, 0, 0);
        SDL_RenderPresent(renderer);
    }

    void clean() {
        Game::clean();
        textureManager->Free();
    }

};