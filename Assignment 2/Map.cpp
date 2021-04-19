#include "Tile.cpp"
#include <vector>
#include<fstream>

class Map{

private:
    int height;
    int width;
    string path;
    vector<vector<Tile*>> tileStruct;

    int playerPos[2];
    int blinkyPos[2];
    int inkyPos[2];
    int pinkyPos[2]; 
    int clydePos[2];

public:

    Map(string pathM) {
        path=pathM;
    }

    bool genrateMap(TextureSet *TextureManager){
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
        int y=count-1;
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
                        playerPos[0]=x;
                        playerPos[1]=y;
                        break;
                    case 'b':
                        tile=new Tile(x,y,false,false);
                        blinkyPos[0]=x;
                        blinkyPos[1]=y;
                        break;
                    case 'i':
                        tile=new Tile(x,y,false,false);
                        inkyPos[0]=x;
                        inkyPos[1]=y;
                        break;
                    case 'n':
                        tile= new Tile(x,y,false,false);
                        pinkyPos[0]=x;
                        pinkyPos[1]=y;
                        break;
                    case 'c':
                        tile= new Tile(x,y,false,false);
                        clydePos[0]=x;
                        clydePos[1]=y;
                        break;
                    case ' ':
                        tile= new Tile(x,y,false,false);
                        break;
                }
                if (tile!=NULL){
                    tile->setTexture(TextureManager);
                    trow.push_back(tile);
                }
            }
            tileStruct.insert(tileStruct.begin(),trow);
            y--;
        }
        width=tileStruct[0].size();
        file.close();
        file1.close();
        return true;
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