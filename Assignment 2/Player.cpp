#include "Map.cpp"

using namespace std;


class Player{

private:

    int speed = 3;
    int score = 0;
    int maxLife = 3;
    int lifeLeft = 3;

    int xBound;
    int yBound;

    bool visible = true;
    int playMode = 0;

    bool alive = true;
    bool animating = false;

    Texture *texture = NULL;
    Tile *currTile = NULL;
    Tile *nextTile = NULL;

    void handleBound(int& x, int bound) {
        if (x >= bound) {
            x = x%bound;
        }
        
        else if (x < 0) {
            x = (x+bound)%bound;
        }
    }

public: 

    static Map* map;

    Player(Texture *playerTexture, Tile *initTile){
        texture = playerTexture;
        currTile = initTile;

    }

    ~Player() {
        texture = NULL;
        currTile = NULL;
        nextTile = NULL;
    }

    void setBounds(int height, int width) {
        xBound = width;
        yBound = height;
    }

    void setMaxLife(int max) {maxLife = max;}
    void setSpeed(int s) {speed = s;}
    void setWASD() {playMode =1;}

    int getScore() {return score;}
    int getLifeLeft() {return lifeLeft;}
    bool isAlive() {return alive;}
    bool isAnimating() {return animating;}

    void movement(SDL_Event *event) {
        int currX = currTile->getX();
        int currY = currTile->getY();

        int nextX = currX;
        int nextY = currY;

        SDL_PollEvent(event);

        if (event->type == SDL_KEYDOWN) {

            switch (event->key.keysym.sym){
                case SDLK_UP:

                    nextY += 1; 
                    handleBound(nextY, yBound);                
                    break;

                case SDLK_DOWN:
                    
                    nextY -= 1;
                    handleBound(nextY, yBound);
                    break;

                case SDLK_RIGHT:
                    
                    nextX += 1;
                    handleBound(nextX, xBound);
                    break;

                case SDLK_LEFT:
                    
                    nextX -= 1;
                    handleBound(nextX, xBound);
                    break;
            }
	    }
        nextTile = map->getTile(nextX,nextY);

        if (nextTile != NULL) {

            if (nextTile->isCoin) {
                score+= 1;
                nextTile->isCoin = false;
            }
            
            if (nextTile->getBrick() == false) {
                currTile = nextTile;
            }
        }
        
    }

    void update() {

        if (animating) {

        }

        else  {
            if (visible) {
            }
        }
    }

    void render() {

        if (visible) {
            if (animating) {

            }
            else {

            }
        }

    }

};