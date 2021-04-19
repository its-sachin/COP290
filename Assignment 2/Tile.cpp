#include "TextureSet.cpp"

class Tile{

private:

    int xpos;
    int ypos;
    bool isBrick = false;   
    Texture *texture = NULL;

public:
    
    bool isCoin = false; 
    
    Tile(int x, int y, bool brick, bool coin) {
        xpos = x;
        ypos = y;
        isBrick = brick;
        isCoin = coin;
    }

    ~Tile() {
        texture = NULL;
    }

    void setTexture(TextureSet* TextureManager) {

        if (isBrick) {
            texture = TextureManager->getTexture("brick");
        }

        if (isCoin) {
            texture = TextureManager->getTexture("coin");
        }

        else {
            texture = NULL;
        }
    }

    int getX() {return xpos;}
    int getY() {return ypos;}
    bool getBrick() {return isBrick;}



};