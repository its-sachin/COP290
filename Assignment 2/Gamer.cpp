#include "Sprites.cpp"

class Gamer{

protected:


    int xBound;
    int yBound;

    bool visible = true;
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