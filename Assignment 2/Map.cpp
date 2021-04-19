#include "Tile.cpp"

class Map{

private:
    int height;
    int width;
    Tile*** tileStruct;

    int playerPos[2];
    int blinkyPos[2];
    int inkyPos[2];
    int pinkyPos[2]; 
    int clydePos[2];

public:

    Map(string path) {
        //initialise

        //here read the text file provided and make tiles, sstore them in tileStruct
        // if "." then make isCoin true
        // if "x" then make isBrick true;
        // if "p" then set playerPos[2] to (i,j)
        // if "e1" then set blinkyPos[2] to (i,j)
        // same for other enemy

        // when we will create the instance of map class in oure pacman class we will get these initial positions and 
        // use then to inittialise oue player and enemy
    }

    int getHeight() {return height;}
    int getWidth() {return width;}

    int* getPlayerPos(){return playerPos;}
    int* getBlinkyPos(){return blinkyPos;}
    int* getInkyPos(){return inkyPos;}
    int* getPinkyPos(){return pinkyPos;}
    int* getClydePos(){return clydePos;}

    Tile* getTile(int x, int y) {
        if (x<width && y<height){
            return tileStruct[x][y];
        }
        else {
            return NULL;
        }
    }


};