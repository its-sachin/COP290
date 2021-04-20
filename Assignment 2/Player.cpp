#include "Map.cpp"

using namespace std;


class Player{

private:

    int speed = 3;
    int score = 0;
    int maxLife = 3;
    int lifeLeft = 3;

    int xBound;
    int yBound;

    bool visible = true;
    int playMode = 0;

    bool alive = true;
    bool animating = false;

    Tile *currTile = NULL;
    Tile *nextTile = NULL;
    Texture *texture = NULL;

    void handleBound(int& x, int bound) {
        if (x >= bound) {
            x = x%bound;
        }
        
        else if (x < 0) {
            x = (x+bound)%bound;
        }
    }

public: 


    Player(Texture *playerTex){
        texture = playerTex;
    }

    ~Player() {
        currTile = NULL;
        nextTile = NULL;
        texture = NULL;
    }

    void setInitTile(Tile* initTile) {
        currTile = initTile;
        cout << "init x" << currTile->getX() << " init y " << currTile->getY()<<endl;
        nextTile = NULL;
    }

    void setBounds(int height, int width) {
        xBound = width;
        yBound = height;
    }

    void setMaxLife(int max) {maxLife = max;}
    void setSpeed(int s) {speed = s;}
    void setWASD() {playMode =1;}

    int getScore() {return score;}
    int getLifeLeft() {return lifeLeft;}
    bool isAlive() {return alive;}
    bool isAnimating() {return animating;}

    void movement(SDL_Event *event,Map *map) {
        int currX = currTile->getX();
        int currY = currTile->getY();

        int nextX = currX;
        int nextY = currY;

        SDL_PollEvent(event);

        if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {

            switch (event->key.keysym.sym){
                case SDLK_UP:

                    cout<<"up"<<endl;
                    cout<< "before y:" << nextY << endl;
                    nextY -= 1; 
                    handleBound(nextY, yBound);                
                    cout<<"after y:" << nextY<<endl;                    
                    break;

                case SDLK_DOWN:
                    
                    cout<<"doen"<<endl;
                    cout<< "before y:" << nextY << endl;
                    nextY += 1;
                    handleBound(nextY, yBound);
                    cout<<"after y:" << nextY<<endl;                    
                    break;

                case SDLK_RIGHT:
                    
                    cout<<"right"<<endl;
                    cout<< "before x:" << nextX << endl;
                    nextX += 1;
                    handleBound(nextX, xBound);
                    cout<<"after x:" << nextX<<endl;                    
                    break;

                case SDLK_LEFT:
                    
                    cout<<"left"<<endl;
                    cout<< "before x:" << nextX << endl;
                    nextX -= 1;
                    handleBound(nextX, xBound);
                    cout<<"after x:" << nextX<<endl;                    
                    break;
            }
            nextTile = map->getTile(nextX,nextY);
	    }

        if (nextTile != NULL) {
            cout << "nextTile not null" << endl;

            if (nextTile->isCoin) {
                score+= 1;
                nextTile->isCoin = false;
            }
            
            if (nextTile->getBrick() == false) {
                cout << "changing current tile" << endl;
                currTile = nextTile;
            }

            nextTile = NULL;
        }
        
    }

    void update(SDL_Event *event, Map *map) {

        if (animating) {

        }

        else  {
            if (visible) {
                movement(event, map);
            }
        }
    }

    void render(int tileWidth, int tileHeight) {

        SDL_Rect src = {0,0,25,25};

        texture->render(currTile->getX()*tileWidth,currTile->getY()*tileHeight,&src);
    }


};