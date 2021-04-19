#include "Tile.cpp"

class Map{

private:
    int height;
    int width;
    Tile*** tileStruct; 

public:

    Map(string path) {
        //initialise
    }

    int getHeight() {return height;}
    int getWidth() {return width;}

    Tile* getTile(int x, int y) {
        if (x<width && y<height){
            return tileStruct[x][y];
        }
        else {
            return NULL;
        }
    }


};