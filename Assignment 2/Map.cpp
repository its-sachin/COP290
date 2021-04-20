#include "Tile.cpp"
#include <vector>
#include<fstream>

class Map{

private:
    int height;
    int width;
    string path;
    vector<vector<Tile*>> tileStruct;
    int Screenx;
    int Screeny;

    Tile *playerInit = NULL;
    Tile *blinkyInit = NULL;
    Tile *inkyInit = NULL;
    Tile *pinkyInit = NULL; 
    Tile *clydeInit = NULL;

public:

    Map(string pathM, int winWidth, int winHeight) {
        path=pathM;
        Screenx = winWidth;
        Screeny = winHeight;
    }

    bool genrateMap(){
        fstream file;
        file.open(path.c_str(), std::ios::in);
        if (file.is_open() == false){
            return false;
        }
        int count = 0;
        string line1;
    
        while (getline(file, line1)){
           count++;
        }
        height=count;
        fstream file1;
        file1.open(path.c_str(), std::ios::in);
        string line;

        int x=0;
        int y=0;
        while (std::getline(file1, line)) {
            vector<Tile*> trow;
            vector<char> chars(line.begin(), line.end());

            for (int x = 0; x < chars.size(); x++) {
                Tile* tile=NULL;
                switch (chars[x])
                {
                    case 'x':
                        tile= new Tile(x,y,true,false);
                        break;
                    case '.':
                        tile= new Tile(x,y,false,true);
                        break;
                    case 'p':
                        tile=new Tile(x,y,false,false);
                        playerInit = tile;
                        break;
                    case 'b':
                        tile=new Tile(x,y,false,false);
                        blinkyInit = tile;
                        break;
                    case 'i':
                        tile=new Tile(x,y,false,false);
                        inkyInit = tile;
                        break;
                    case 'n':
                        tile= new Tile(x,y,false,false);
                        pinkyInit = tile;
                        break;
                    case 'c':
                        tile= new Tile(x,y,false,false);
                        clydeInit = tile;
                        break;
                    case ' ':
                        tile= new Tile(x,y,false,false);
                        break;
                }
                if (tile!=NULL){
                    trow.push_back(tile);
                }
            }
            tileStruct.push_back(trow);
            y++;
        }
        width=tileStruct[0].size();
        file.close();
        file1.close();
        return true;
    }

    int getHeight() {return height;}
    int getWidth() {return width;}

    Tile* getPlayerInit(){return playerInit;}
    Tile* getBlinkInits(){return blinkyInit;}
    Tile* getInkyInit(){return inkyInit;}
    Tile* getPinkyInit(){return pinkyInit;}
    Tile* getClydeInit(){return clydeInit;}

    Tile* getTile(int x, int y) {
        if (x<height && y<width){
            return tileStruct[x][y];
        }
        else {
            return NULL;
        }
    }


};