#include "Sprites.cpp"
#include "Enum.cpp"


int stoneTime=0;
class Gamer{

protected:


    int xBound;
    int yBound;

    bool visible = true;
    bool animating = false;

    int xRel;
    int yRel;
    int psuedoRel = TILE_HEIGHT;

    UD currUD=FRONT;
    UD nextUD=FRONT;
    //0-front
    //1-down
    //2-up

    LR currLR =LEFT;
    LR nextLR =LEFT;
    //0-left
    //1-right

    Tile *currTile = NULL;
    Tile *nextTile = NULL;
    Tile *initTile = NULL;
    Texture *texture = NULL;
    Sprites *sprite = NULL;

    pair<int,int> exactPos;

    void handleBound(int& x, int bound) {
        if (x >= bound) {
            x = x%bound;
        }
        
        else if (x < 0) {
            x = (x+bound)%bound;
        }
    }

    void initRel() {
        animating = true;
        xRel = (nextTile->getX() - currTile->getX())*TILE_WIDTH;
        yRel = (nextTile->getY() - currTile->getY())*TILE_HEIGHT;
    }

    void updateRel() {

        if (xRel < 0) {
            xRel += 1;
        }

        else if (xRel >0 ) {
            xRel -=1;
        }
        
        if (yRel < 0) {
            yRel += 1;
        }

        else if (yRel >0 ) {
            yRel -=1;
        }
    }

public: 

    void free() {
        currTile = NULL;
        nextTile = NULL;
        // prevTile =NULL;
        texture = NULL;
        initTile = NULL;

        sprite->~Sprites();
        sprite = NULL;
    }

    void setInitTile(Tile* initialTile) {
        initTile = initialTile;
        currTile = initTile;
        nextTile = NULL;
        // prevTile=initialTile;
    }

    void setBounds(int height, int width) {
        xBound = width;
        yBound = height;
    }

    pair<int,int> getExactPos() {
        return exactPos;
    }

    bool isAnimating() {return animating;}
    Tile* getcurrTile(){
        return currTile;
    }

    void render() {

        if (nextLR == currLR) {

            if (currUD == nextUD) {

                if (animating == false) {
                    animating  = true;
                }

                SDL_Rect *src = sprite->getRect(currUD,currLR);

                texture->render(currTile->getX()*TILE_WIDTH -xRel,currTile->getY()*TILE_HEIGHT - yRel,src);
                exactPos = {currTile->getX()*TILE_WIDTH -xRel,currTile->getY()*TILE_HEIGHT- yRel};

                updateRel();
                psuedoRel -= 1;
                if (psuedoRel == 0) {
                    animating = false;
                    psuedoRel = TILE_HEIGHT;
                }

            }

            else {


                SDL_Rect *src =NULL;

                if (abs(xRel) > TILE_WIDTH || abs(xRel) > TILE_WIDTH) {

                    src = sprite->getRect(FRONT,currLR);
                    texture->render(currTile->getX()*TILE_WIDTH- xRel,currTile->getY()*TILE_HEIGHT- yRel,src);
                    exactPos = {currTile->getX()*TILE_WIDTH -xRel,currTile->getY()*TILE_HEIGHT- yRel};

                    
                }

                else {
                    src = sprite->getRect(nextUD ,currLR);
                    texture->render(currTile->getX()*TILE_WIDTH- xRel,currTile->getY()*TILE_HEIGHT- yRel,src);
                    exactPos = {currTile->getX()*TILE_WIDTH -xRel,currTile->getY()*TILE_HEIGHT- yRel};
                }
                
                updateRel();
                if (xRel ==0 && yRel ==0) {
                    animating = false;
                    currUD = nextUD;
                    psuedoRel = TILE_HEIGHT;
                }

                
            }
        }

        else {


            SDL_Rect *src =NULL;

            if (abs(xRel) > TILE_WIDTH || abs(xRel) > TILE_WIDTH) {

                src = sprite->getRect(nextUD,currLR);
                texture->render(currTile->getX()*TILE_WIDTH- xRel,currTile->getY()*TILE_HEIGHT- yRel,src);
                exactPos = {currTile->getX()*TILE_WIDTH -xRel,currTile->getY()*TILE_HEIGHT- yRel};
            }

            else {

                src = sprite->getRect(currUD ,nextLR);
                texture->render(currTile->getX()*TILE_WIDTH- xRel,currTile->getY()*TILE_HEIGHT- yRel,src);
                exactPos = {currTile->getX()*TILE_WIDTH -xRel,currTile->getY()*TILE_HEIGHT- yRel};

            }            

            updateRel();
            if (abs(xRel) < TILE_WIDTH && abs(xRel) < TILE_WIDTH) {
                currUD = nextUD;
            }

            if (abs(xRel) ==0 && yRel ==0) {
                animating = false;
                currLR = nextLR;
                psuedoRel = TILE_HEIGHT;
            }

        }


    }


};