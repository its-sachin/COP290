#include "Tile.cpp"
#include <vector>

class Map{

private:
    int height;
    int width;
    vector<vector<Tile*>>* tileStruct;

    int playerPos[2];
    int blinkyPos[2];
    int inkyPos[2];
    int pinkyPos[2]; 
    int clydePos[2];

public:

    Map(string path) {
        std::fstream file;
        file.open(path.c_str(), std::ios::in);

        if (file.is_open() == false)
            return false;

        int count = 0;
        std::string line1;
    
        while (getline(file, line)){
           count++;
        }
        height=count;
        file.open(path.c_str(), std::ios::in);
        std::string line;

        int x=0;
        int y=count-1;

        vector<vector<Tile*>> tStruct;

        while (std::getline(file, line)) {
            vector<Tile*> trow;

            std::vector<char> chars(line.begin(), line.end());

            for (unsigned int x = 0; x < chars.size(); x++) {
                
                Tile tile;

                switch (chars[x])
                {
                    case 'x':
                        tile= Tile(x,y,true,false);
                        break;
                    case '.':
                        tile= Tile(x,y,false,true);
                        break;
                    case 'p':
                        tile= Tile(x,y,false,false);
                        playerPos[0]=x;
                        playerPos[1]=y;
                        break;
                    case 'b':
                        tile= Tile(x,y,false,false);
                        blinkyPos[0]=x;
                        blinkyPos[1]=y;
                        break;
                    case 'i':
                        tile= Tile(x,y,false,false);
                        inkyPos[0]=x;
                        inkyPos[1]=y;
                        break;
                    case 'n':
                        tile= Tile(x,y,false,false);
                        pinkyPos[0]=x;
                        pinkyPos[1]=y;
                        break;
                    case 'c':
                        tile= Tile(x,y,false,false);
                        clydePos[0]=x;
                        clydePos[1]=y;
                        break;
                    case ' ':
                        tile= Tile(x,y,false,false);
                        break;
                }

                if (tile != NULL)
                    trow.push_back(tile&);
            }
            tStruct.insert(tStruct.begin(),trow);
            y--;
        }
        width=tStruct[0].size();
        file.close();
        tileStruct=tStruct&;
            //initialise

        //here read the text file provided and make tiles, sstore them in tileStruct
        // if "." then make isCoin True,
        // if "x" then make isBrick True;
        // if "p" then set playerpos[2] to (i,j)
        // if "e1" then set blinkypos[2] to (i,j)
        // same for other enemies
        // when we will create the instance of map class in oure pacman class we will get these initial position and 
        // use then to inittialise our player and enemy
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