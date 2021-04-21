#include "Sprites.cpp"


class Player{

private:

    int score = 0;
    int maxLife = 3;
    int lifeLeft = 3;

    int xBound;
    int yBound;

    bool visible = true;
    int playMode = 0;

    bool alive = true;
    bool animating = false;

    int currDir=3;
    int nextDir=0;
    //1-down
    //2-up
    //3-left
    //4-right

    Uint32 start;
    int spend;

    Tile *currTile = NULL;
    Tile *nextTile = NULL;
    Texture *texture = NULL;
    Sprites *sprite = NULL;

    void handleBound(int& x, int bound) {
        if (x >= bound) {
            x = x%bound;
        }
        
        else if (x < 0) {
            x = (x+bound)%bound;
        }
    }

public: 


    Player(Texture *playerTex){
        texture = playerTex;
        sprite = new Sprites(playerTex);
    }

    ~Player() {
        currTile = NULL;
        nextTile = NULL;
        texture = NULL;

        sprite->~Sprites();
        sprite = NULL;
    }

    void setInitTile(Tile* initTile) {
        currTile = initTile;
        nextTile = NULL;
    }

    void setBounds(int height, int width) {
        xBound = width;
        yBound = height;
    }

    void setMaxLife(int max) {maxLife = max;}
    void setWASD() {playMode =1;}

    int getScore() {return score;}
    int getLifeLeft() {return lifeLeft;}
    bool isAlive() {return alive;}
    bool isAnimating() {return animating;}
    Tile* getcurrTile(){
        return currTile;
    }

    void movement(SDL_Event *event,Map *map) {
        int currX = currTile->getX();
        int currY = currTile->getY();

        int nextX = currX;
        int nextY = currY;

        SDL_PollEvent(event);

        if (event->type == SDL_KEYDOWN) {


            switch (event->key.keysym.sym){
                case SDLK_UP:

                    nextY -= 1; 
                    nextDir = 2;
                    handleBound(nextY, yBound);                                   
                    break;

                case SDLK_DOWN:
                    
                    nextY += 1;
                    nextDir = 1;
                    handleBound(nextY, yBound);                    
                    break;

                case SDLK_RIGHT:
                    
                    nextX += 1;
                    nextDir = 4;
                    handleBound(nextX, xBound);                   
                    break;

                case SDLK_LEFT:
                    
                    nextX -= 1;
                    nextDir = 3;
                    handleBound(nextX, xBound);                    
                    break;
            }
            nextTile = map->getTile(nextX,nextY);
	    }

        if (nextTile != NULL) {

            if (nextTile->isCoin) {
                score+= 1;
                nextTile->isCoin = false;

                currTile = nextTile;
            }
            
            else if (nextTile->getBrick() == false) {
                currTile = nextTile;
            }

            nextTile = NULL;
            animating = true;
        }
        
    }

    void update(SDL_Event *event, Map *map) {

        if (animating) {
            spend = SDL_GetTicks() - start;

            if (FRAME_DELAY*SPEED <= spend) {
                animating = false;
            }
        }

        else  {
            if (visible) {
                start = SDL_GetTicks();
                movement(event, map);
            }
        }
    }

    void render() {

        if (nextDir == 0) {

            SDL_Rect *src = sprite->getRect(currDir);

            texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);
        }

        else {

            Uint32 start1;
            int spend1;

            start1 = SDL_GetTicks();

            SDL_Rect *src =NULL;
            
            src = sprite->getRect(0);
            texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);

            spend1 = SDL_GetTicks() - start1;

            if (FRAME_DELAY > spend1) {
                SDL_Delay(FRAME_DELAY- spend1);
            }

            src = sprite->getRect(nextDir);
            texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);

            currDir = nextDir;
            nextDir= 0;
        }


    }


};