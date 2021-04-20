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

    Texture a;

    public:

    SDL_Event event;

    void init(string title, int width, int height) {

        const char* temp = title.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height);
        if (isRunning) {
            winWidth = width;
            winHeight = height;

            a.Load("Assets/Images/brick.bmp");

            textureManager = new TextureSet("Assets/Images");
            map = new Map("Assets/Maps/map1.txt", winWidth, winHeight);
            map->genrateMap(textureManager);

            // a = textureManager->getTexture("brick");
        }

    }


    void render(){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        
        a.render(0,0);
        textureManager->render("brick", 10,10);
        renderBricks();

        SDL_RenderPresent(renderer);
    }

    void clean() {
        Game::clean();
        textureManager->~TextureSet();
        a.free();
    }


    void renderBricks() {
        Texture tex = textureManager->getTexture("brick");

        int x,y;
        for (int i=0; i < map->getHeight(); i++) {

            for (int j=0; j< map->getWidth(); j++) {
                if ((map->getTile(i,j) != NULL) && map->getTile(i,j)->getBrick()) {
                    x = tileWidth*j;
                    y = tileHeight*i;
                    tex.render(x,y);
                }
            }
        }
        
    }

};