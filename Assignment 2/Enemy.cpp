#include "Player.cpp"

using namespace std;


class Enemy{

private: 
    int speed=2;

    int xbound;
    int ybound;

    bool visible=true;

    int state;

    bool animating=false;

    bool moving=false;

    int direction;

    Tile *currTile=NULL;
    Tile *nextTile=NULL;
    Texture *texture=NULL;

    void handleBound(int &x, int bound) {
    if (x >= bound) {
            x = x%bound;
        }
        
    else if (x < 0) {
            x = (x+bound)%bound;
        }
    }
public: 

    Enemy(Texture *enemyTex){
        texture = enemyTex;
    }

    ~Enemy(){
        currTile=NULL;
        nextTile=NULL;
        texture=NULL;
    }
    void setInitTile(Tile* initTile) {
        currTile = initTile;
        nextTile = NULL;
    }

    void setBounds(int height, int width) {
        xbound = width;
        ybound = height;
    }
    void setSpeed(int s) {speed = s;}
    void setState(int s) {state = s;}
    bool isAnimating() {return animating;}


    void movement(Map *map) {
        int currX = currTile->getX();
        int currY = currTile->getY();
        int nextX = currX;
        int nextY = currY;

        int temp1=currX+1;
        int temp2=currY+1;
        int temp3=currY-1;
        int temp4=currX-1;

        handleBound(temp1,xbound);
        handleBound(temp2,ybound);
        handleBound(temp3,ybound);
        handleBound(temp4,xbound);
        
        int nextXX[4]={temp1,currX,currX,temp4};
        int nextYY[4]={currY,temp2,temp3,currY};
        int i=rand()%4;
        while(true) {
            nextX=nextXX[i];
            nextY=nextYY[i];
            nextTile=map->getTile(nextX,nextY);
            if (nextTile->getBrick()== false){
                break;
            }
            i++;
            handleBound(i,4);
        }
        currTile = nextTile;
        nextTile = NULL;
    }

    void update( Map *map) {

        if (animating) {

        }

        else  {
            if (visible) {
                movement(map);
            }
        }
    }

    void render(int tileWidth, int tileHeight) {

        SDL_Rect src = {0,0,25,25};

        texture->render(currTile->getX()*tileWidth,currTile->getY()*tileHeight,&src);
    }

};