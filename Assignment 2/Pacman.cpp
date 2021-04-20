#include "Enemy.cpp"



class Pacman: public Game, public TextureSet{
    private:
    Player *Thanos = new Player(&player1);

    Enemy *Blinky;
    Enemy *Pinky;
    Enemy *Inky ;
    Enemy *Clyde;

    int winWidth; 
    int winHeight;

    int tileWidth = 30;
    int tileHeight = 30;

    Map *map = NULL; 


    public:

    SDL_Event event;

    void init(string title, int width, int height) {

        const char* temp = title.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height);
        if (isRunning) {
            winWidth = width;
            winHeight = height;

            // a.Load("Assets/Images/brick.bmp");

            loadTex("Assets/Images");
            map = new Map("Assets/Maps/map1.txt", winWidth, winHeight);
            map->genrateMap();

            Thanos->setBounds(map->getHeight(),map->getWidth());
            Thanos->setInitTile(map->getPlayerInit());
        }

    }


    void render(){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        renderBack();

        Thanos->render(tileWidth, tileHeight);

        SDL_RenderPresent(renderer);
    }

    void update() {
        Thanos->update(&event,map);
    }

    void clean() {
        Game::clean();
        freeTex();
    }


    void renderBack() {

        int x,y;
        for (int i=0; i < map->getHeight(); i++) {

            for (int j=0; j< map->getWidth(); j++) {
                Tile *currTile = map->getTile(i,j);
                if ((currTile != NULL)) {
                    x = tileWidth*j;
                    y = tileHeight*i;

                    if (currTile->getBrick()) {
                        brick.render(x,y);
                    }

                    else if (currTile->isCoin) {
                        coin.render(x,y);
                    }
                }
            }
        }
        
    }

};