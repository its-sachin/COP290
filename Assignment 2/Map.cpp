#include "Tile.cpp"
#include <vector>
#include<fstream>

class Map{

private:
    int height;
    int width;
    string path;
    vector<vector<Tile*>> tileStruct;

    int tilex;
    int tiley;
    int Screenx;
    int Screeny;

    int playerPos[2];
    int blinkyPos[2];
    int inkyPos[2];
    int pinkyPos[2]; 
    int clydePos[2];

public:

    Map(string pathM, int tileWidth, int tileHeight, int winWidth, int winHeight) {
        path=pathM;

        tilex = tileWidth;
        tiley= tileHeight;
        Screenx = winWidth;
        Screeny = winHeight;
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

    void setBricks(SDL_Renderer *renderer) {
        SDL_Surface *surface = SDL_LoadBMP("Assets/Images/brick.bmp");
        SDL_Texture *map_texture;
        SDL_Rect rect;
        rect.w = tilex;
        rect.h = tiley;
        SDL_Texture *tex = NULL;
        
        tex = SDL_CreateTextureFromSurface(renderer, surface);

        map_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Screenx, Screeny);
        SDL_SetRenderTarget(renderer, map_texture);

        for (int i=0; i < height; i++) {

            for (int j=0; j< width; j++) {
                if ((getTile(i,j) != NULL) && getTile(i,j)->getBrick()) {
                    rect.x = tilex*j;
                    rect.y = tiley*i;
                    SDL_RenderCopy(renderer, tex, NULL, &rect);
                }
            }
        }
        
        SDL_SetRenderTarget(renderer, NULL);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, tex, NULL, NULL);
        SDL_RenderPresent(renderer);
        
    }


};