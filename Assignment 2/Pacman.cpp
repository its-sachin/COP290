#include "Enemy.cpp"




class Pacman: public Game, public TextureSet{
    private:
    Player *Thanos = new Player(&player1);

    Enemy *Blinky;
    Enemy *Pinky;
    Enemy *Inky ;
    Enemy *Clyde;

    Map *map = NULL; 


    public:

    SDL_Event event;

    void init() {

        const char* temp = WIN_NAME.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT);
        if (isRunning) {

            loadTex("Assets/Images");
            map = new Map("Assets/Maps/map1.txt");
            map->genrateMap();

            Thanos->setBounds(map->getHeight(),map->getWidth());
            Thanos->setInitTile(map->getPlayerInit());
        }

    }


    void render(){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        renderBack();

        Thanos->render();

        SDL_RenderPresent(renderer);
    }

    void update() {
        Thanos->update(&event,map);
    }

    void clean() {
        freeTex();
        cout << "Score " << Thanos->getScore() << endl;
        Thanos->~Player();
        map->~Map();

        Game::clean();
    }


    void renderBack() {

        int x,y;
        for (int j=0; j < map->getHeight(); j++) {

            for (int i=0; i< map->getWidth(); i++) {
                Tile *currTile = map->getTile(i,j);
                if ((currTile != NULL)) {
                    x = TILE_WIDTH*i;
                    y = TILE_HEIGHT*j;

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