#include "Gamer.cpp"


class Player : public Gamer{

private:

    int score = 0;
    int maxLife = 3;
    int lifeLeft = 3;

    int playMode = 0;

    bool alive = true;

    int currDir=3;
    int nextDir=0;
    //1-down
    //2-up
    //3-left
    //4-right


public: 


    Player(Texture *playerTex){
        texture = playerTex;
        sprite = new Sprites(playerTex);
    }

    ~Player() {
        free();
    }


    void setMaxLife(int max) {maxLife = max;}
    void setWASD() {playMode =1;}

    int getScore() {return score;}
    int getLifeLeft() {return lifeLeft;}
    bool isAlive() {return alive;}
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
                    nextUD = 2;
                    handleBound(nextY, yBound);                                   
                    break;

                case SDLK_DOWN:
                    
                    nextY += 1;
                    nextUD = 1;
                    handleBound(nextY, yBound);                    
                    break;

                case SDLK_RIGHT:
                    
                    nextX += 1;
                    nextLR = 1;
                    nextUD = 0;
                    handleBound(nextX, xBound);                   
                    break;

                case SDLK_LEFT:
                    
                    nextX -= 1;
                    nextLR = 0;
                    nextUD = 0;
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


};