#include "Enemy.cpp"




class Pacman: public Game, public TextureSet{
    private:
    Player *Thanos = new Player(&player1Tex);
    Player *ThanosPast = new Player(&player2Tex);

    Enemy *Blinky = new Enemy(&blinkyTex, "blinky");
    Enemy *Pinky = new Enemy(&pinkyTex, "pinky");
    Enemy *Inky  = new Enemy(&inkyTex, "inky");
    Enemy *Clyde = new Enemy(&clydeTex, "clyde");

    Map *map = NULL; 

    PlayMode mode = Single;


    public:

    SDL_Event event;

    Pacman(PlayMode m) {
        //0 for singke player
        //1 for multiplayer offline
        //2 for multiplayer online

        mode = m;

    }

    void init() {

        const char* temp = WIN_NAME.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT);
        if (isRunning) {

            loadTex(IMAGES_PATH);
            map = new Map(MAPS_PATH + "/map2.txt");
            map->genrateMap();

            Thanos->setBounds(map->getHeight(),map->getWidth());
            Thanos->setInitTile(map->getPlayerInit());

            if (mode == Doffline || mode == Donline) {
                ThanosPast->setBounds(map->getHeight(),map->getWidth());
                ThanosPast->setInitTile(map->getPlayerInit());

                if (mode == Doffline) {
                    ThanosPast->setWASD();
                }

                Inky->setID("blinky");
                Clyde->setID("pinky");
            }

            Blinky->init(map);
            Pinky->init(map);
            Inky->init(map);
            Clyde->init(map);
        }

    }


    void render(){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        renderBack();

        Blinky->render(); 
        Pinky->render();      
        Inky->render();
        Clyde->render();
        Thanos->render();

        if (mode == Donline || mode == Doffline) {
            ThanosPast->render();
        }

        SDL_RenderPresent(renderer);
    }

    void update() {

        Thanos->update(&event,map);
        Blinky->update(map, Thanos,NULL);
        Pinky->update(map, Thanos,Blinky);

        if (mode ==Single) {
            Inky->update(map, Thanos,Blinky);
            Clyde->update(map, Thanos,Blinky);
        }
        else if (mode == Doffline|| mode == Donline) {
            ThanosPast->update(&event,map);
            Inky->update(map, ThanosPast,NULL);
            Clyde->update(map, ThanosPast,Inky);
        }
        
    }

    void clean() {
        freeTex();

        Thanos->~Player();
        ThanosPast->~Player();

        map->~Map();

        Blinky->~Enemy();
        Pinky->~Enemy();
        Inky->~Enemy();
        Clyde->~Enemy();

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