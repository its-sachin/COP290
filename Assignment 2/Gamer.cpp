#include "Sprites.cpp"
#include "Enum.cpp"

class Gamer{

protected:


    int xBound;
    int yBound;

    bool visible = true;
    bool animating = false;

    UD currUD=FRONT;
    UD nextUD=FRONT;
    //0-front
    //1-down
    //2-up

    LR currLR =LEFT;
    LR nextLR =LEFT;
    //0-left
    //1-right


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


    void free() {
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

    bool isAnimating() {return animating;}
    Tile* getcurrTile(){
        return currTile;
    }

    void render() {

        Uint32 start1;
        int spend1;

        if (nextLR == currLR) {

            if (currUD == nextUD) {

                SDL_Rect *src = sprite->getRect(currUD,currLR);

                texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);

            }

            else {
                
                start1 = SDL_GetTicks();

                SDL_Rect *src =NULL;
                
                src = sprite->getRect(FRONT,currLR);
                texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);

                spend1 = SDL_GetTicks() - start1;

                if (FRAME_DELAY > spend1) {
                    SDL_Delay(FRAME_DELAY- spend1);
                }

                src = sprite->getRect(nextUD ,currLR);
                currUD = nextUD;
                texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);
            }
        }

        else {

                
            start1 = SDL_GetTicks();

            SDL_Rect *src =NULL;
            
            src = sprite->getRect(nextUD,currLR);
            currUD = nextUD;
            texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);

            spend1 = SDL_GetTicks() - start1;

            if (FRAME_DELAY > spend1) {
                SDL_Delay(FRAME_DELAY- spend1);
            }

            src = sprite->getRect(currUD ,nextLR);
            currLR = nextLR;
            texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,src);

        }


    }


};