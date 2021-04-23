#include "Gamer.cpp"


class Player : public Gamer{

private:

    int score = 0;
    int maxLife = 3;
    int lifeLeft = 3;

    MoveType mode = ULDR;

    bool alive = true;
    Stone stone = NONE;

public: 


    Player(Texture *playerTex){
        texture = playerTex;
        sprite = new Sprites(playerTex);
    }

    ~Player() {
        free();
    }

    void setStone(Stone s){stone =s;}
    Stone getStone(){return stone;}
    void setMaxLife(int max) {maxLife = max;}
    int getScore() {return score;}
    int getLifeLeft() {return lifeLeft;}
    bool isAlive() {return alive;}
    int getCurr() {
        if (nextUD == 0) {
            return nextLR;
        }

        else {
            return nextUD;
        }
    }
    Tile* getcurrTile(){
        return currTile;
    }

    void setWASD() {mode = WASD;}

    void movement(SDL_Event *event,Map *map) {
        int currX = currTile->getX();
        int currY = currTile->getY();

        int nextX = currX;
        int nextY = currY;

        SDL_PollEvent(event);

        if (event->type == SDL_KEYDOWN) {

            int currEvent = event->key.keysym.sym;

            switch (mode) {

                case(ULDR):
                    switch (currEvent){
                    case (SDLK_UP):

                        nextY -= 1; 
                        nextUD = UP;
                        handleBound(nextY, yBound);                                   
                        break;

                    case SDLK_DOWN:
                        
                        nextY += 1;
                        nextUD = DOWN;
                        handleBound(nextY, yBound);                    
                        break;

                    case SDLK_RIGHT:
                        
                        nextX += 1;
                        nextLR = RIGHT;
                        nextUD = FRONT;
                        handleBound(nextX, xBound);                   
                        break;

                    case SDLK_LEFT:
                        
                        nextX -= 1;
                        nextLR = LEFT;
                        nextUD = FRONT;
                        handleBound(nextX, xBound);                    
                        break;
                    }
                break;

                case(WASD):

                    switch (currEvent){
                    case (SDLK_w):

                        nextY -= 1; 
                        nextUD = UP;
                        handleBound(nextY, yBound);                                   
                        break;

                    case SDLK_s:
                        
                        nextY += 1;
                        nextUD = DOWN;
                        handleBound(nextY, yBound);                    
                        break;

                    case SDLK_d:
                        
                        nextX += 1;
                        nextLR = RIGHT;
                        nextUD = FRONT;
                        handleBound(nextX, xBound);                   
                        break;

                    case SDLK_a:
                        
                        nextX -= 1;
                        nextLR = LEFT;
                        nextUD = FRONT;
                        handleBound(nextX, xBound);                    
                        break;
                    }
                break;

            }

            
            nextTile = map->getTile(nextX,nextY);
	    }

        if (nextTile != NULL) {

            if (nextTile->isCoin) {
                score+= 1;
                sound->playCoin();
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


};