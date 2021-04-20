#include "TextureSet.cpp"

class Tile{

private:

    int xpos;
    int ypos;
    bool isBrick = false;   

public:
    
    bool isCoin = false; 
    
    Tile(int x, int y, bool brick, bool coin) {
        xpos = x;
        ypos = y;
        isBrick = brick;
        isCoin = coin;
    }


    int getX() {return xpos;}
    int getY() {return ypos;}
    bool getBrick() {return isBrick;}



};