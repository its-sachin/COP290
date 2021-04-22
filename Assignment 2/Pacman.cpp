#include "Enemy.cpp"




class Pacman: public Game, public TextureSet{
    private:
    Player *Thanos = new Player(&player1Tex);

    Enemy *Blinky = new Enemy(&blinkyTex, "blinky");
    Enemy *Pinky = new Enemy(&pinkyTex, "pinky");
    Enemy *Inky  = new Enemy(&inkyTex, "inky");
    Enemy *Clyde = new Enemy(&clydeTex, "clyde");

    Map *map = NULL; 


    public:

    SDL_Event event;

    void init() {

        const char* temp = WIN_NAME.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT);
        if (isRunning) {

            loadTex("Assets/Images");
            map = new Map("Assets/Maps/map2.txt");
            map->genrateMap();

            Thanos->setBounds(map->getHeight(),map->getWidth());
            Thanos->setInitTile(map->getPlayerInit());

            Blinky->init(map);
            Pinky->init(map);
            Inky->init(map);
            Clyde->init(map);
        }

    }


    void render(){
        SDL_SetRenderDrawColor(renderer, 0255,0255,0255,255);
        SDL_RenderClear(renderer);
        renderBack();

        Thanos->render();
        Blinky->render();
        Pinky->render();
        Inky->render();
        Clyde->render();

        SDL_RenderPresent(renderer);
    }

    void update() {
        Thanos->update(&event,map);
        Blinky->update(map, Thanos,NULL);
        cout<<Blinky->getcurrTile()->getX()<<endl;
        Pinky->update(map, Thanos,Blinky);
        Inky->update(map, Thanos,Blinky);
        Clyde->update(map, Thanos,Blinky);
    }

    void clean() {
        freeTex();
        Thanos->~Player();
        map->~Map();
        Blinky->~Enemy();

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
                        brickTex.render(x,y);
                    }

                    else if (currTile->isCoin) {
                        coinTex.render(x,y);
                    }
                }
            }
        }
        
    }

};