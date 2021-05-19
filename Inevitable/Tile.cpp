#include "TextureSet.cpp"

class Tile{

private:

    int xpos;
    int ypos;
    bool isBrick;   

public:
    
    bool isCoin = false; 
    bool isMind = false;

    
    Tile(int x, int y, bool brick, bool coin, bool mind = false) {
        xpos = x;
        ypos = y;
        isBrick = brick;
        isCoin = coin;
        isMind = mind;
    }


    int getX() {return xpos;}
    int getY() {return ypos;}
    bool getBrick() {return isBrick;}



};