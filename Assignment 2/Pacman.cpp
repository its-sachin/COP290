#include "Game.cpp"
#include "Enemy.cpp"


class Pacman: public Game{
    private:
    Player *Thanos;

    Enemy *Blinky;
    Enemy *Pinky;
    Enemy *Inky ;
    Enemy *Clyde;

    int winWidth; 
    int winHeight;

    int tileWidth = 30;
    int tileHeight = 30;

    TextureSet *textureManager = NULL;
    Map *map = NULL; 

    public:

    SDL_Event event;

    void init(string title, int width, int height) {

        const char* temp = title.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height);
        if (isRunning) {
            winWidth = width;
            winHeight = height;
            textureManager = new TextureSet("Assets/Images", renderer);
            map = new Map("Assets/Maps/map1.txt", tileWidth, tileHeight, winWidth, winHeight);
            map->genrateMap(textureManager);
        }

    }

    void render(){
        // textureManager->getTexture("brick")->Draw(renderer, 0, 0);
        map->setBricks(renderer);
        SDL_RenderPresent(renderer);
    }

    void clean() {
        Game::clean();
        textureManager->Free();
    }

};