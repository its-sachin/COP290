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

    SDL_Rect lifeRect = {0,0,30,30};
    SDL_Rect backRect = {0,0,WIN_WIDTH,WIN_HEIGHT};

    bool selected = false;

    string balStr(int n) {
        string out = to_string(n);

        while (out.size() != 4) {
            out = "0" + out;
        } 
        return out;
    }

    public:

    SDL_Event event;


    void init() {

        const char* temp = WIN_NAME.c_str();
        Game::init(temp,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT);
        if (isRunning) {

            loadTex(IMAGES_PATH);
            map = new Map(MAPS_PATH + "/map2.txt");
            map->genrateMap();

            Thanos->setBounds(map->getHeight(),map->getWidth());
            Thanos->setInitTile(map->getPlayerInit());


            Blinky->init(map);
            Pinky->init(map);
            Inky->init(map);
            Clyde->init(map);

            mainMenu();
        }

    }

    void initMode() {

        if (mode == Doffline || mode == Donline) {
            ThanosPast->setBounds(map->getHeight(),map->getWidth());
            ThanosPast->setInitTile(map->getPlayerInit());

            Inky->setID("blinky");
            Clyde->setID("pinky");
        }

    }

    void mainMenu() {
        
        Uint32 start;
        int spend;

        int backCurr = 0;
        int sparkCurr = 225;
        int sciCurr = 140;
        int base = movableBG.getWidth();

        while (isRunning && !selected) {

            start = SDL_GetTicks();

            eventManager(&event);

            SDL_SetRenderDrawColor(renderer, 0,0,0,255);
            SDL_RenderClear(renderer);

            movableBG.renderWM(0,0,&backRect);
            backCurr += 1;
            if (backCurr == base) {
                backCurr = 0;
            }
            
            backRect.x = backCurr;

            logoTex.renderWM(220,100);
            menuFont.renderWM(100,350);
            gameTex.renderWM((WIN_WIDTH-gameTex.getWidth())/2, WIN_HEIGHT-gameTex.getHeight());

            // SDL_Rect a = {0,0,300,250};
            // player2Tex.renderWM(500,300, &a);

            sciTex.Load(IMAGES_PATH + "/sci/" + balStr(sciCurr) + ".png");
            sciTex.renderWM(500,300);

            sparkTex.Load(IMAGES_PATH + "/spark/" + balStr(sparkCurr) + ".png");
            sparkTex.renderWM(275,595);

            if (backCurr%10 ==0 ){

                sciCurr = sciCurr%63 + 140;
                sparkCurr = sparkCurr%51 + 225;
            }

            SDL_RenderPresent(renderer);

            selected = selecMenu();

            

            while (FRAME_DELAY > spend) {
                
                eventManager(&event);

                spend = SDL_GetTicks() - start;
            }
        }
        Blinky->setOffset(SDL_GetTicks()/1000);
        Inky->setOffset(SDL_GetTicks()/1000);
        Pinky->setOffset(SDL_GetTicks()/1000);
        Clyde->setOffset(SDL_GetTicks()/1000);
        initMode();
    }


    void render(){

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        Uint32 start = SDL_GetTicks();

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

        int spend = SDL_GetTicks() - start;

        while (spend < SPEED*FRAME_DELAY/(60*35)) {
            spend = SDL_GetTicks() - start;

            eventManager(&event);
        }
    }

    void update() {

        setMovement();
        Blinky->update(map, Thanos,NULL);
        Pinky->update(map, Thanos,Blinky);

        if (mode ==Single) {
            Inky->update(map, Thanos,Blinky);
            Clyde->update(map, Thanos,Blinky);
        }
        else if (mode == Doffline|| mode == Donline) {
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
        scoreBackTex.renderWM(5,10);
        renderScore2(Thanos->getScore(), 85,60);

        for (int i=0; i< Thanos->getLifeLeft(); i++) {
            player1Tex.renderWM(40*i +150,40,&lifeRect);
        }

        if (mode ==Doffline || mode == Donline) {
            scoreBackTex.renderWM(WIN_WIDTH - (scoreBackTex.getWidth() +5) ,10, NULL, SDL_FLIP_HORIZONTAL);
            renderScore2(ThanosPast->getScore(), WIN_WIDTH - 110,60);

            // for (int i=0; i< Thanos->getLifeLeft(); i++) {
            //     player2Tex.renderWM(40*i +150,37,&lifeRect);
            // }
        }
    }

    void setMovement() {
        if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym){
            case SDLK_UP:
                Thanos->update(MOVE_UP,map);           
                break;

            case SDLK_DOWN:
                Thanos->update(MOVE_DOWN,map);                  
                break;

            case SDLK_RIGHT:
                Thanos->update(MOVE_RIGHT,map);
                break;

            case SDLK_LEFT:
                Thanos->update(MOVE_LEFT,map);              
                break;

            case SDLK_w:
                if (mode ==Doffline) {
                    ThanosPast->update(MOVE_UP,map);
                }           
                break;

            case SDLK_s:
                if (mode ==Doffline) {
                    ThanosPast->update(MOVE_DOWN,map);
                }                
                break;

            case SDLK_d:
                if (mode ==Doffline) {
                    ThanosPast->update(MOVE_RIGHT,map);
                }
                break;

            case SDLK_a:
                if (mode ==Doffline) {
                    ThanosPast->update(MOVE_LEFT,map);
                }              
                break;
            }
        }
    }

    bool selecMenu() {

        if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym){
            case SDLK_s:
                mode = Single;           
                return true;

            case SDLK_d:
                mode = Doffline;           
                return true;

            case SDLK_o:
                mode = Donline;           
                return true;
            }
        }

        return false;
    }

};