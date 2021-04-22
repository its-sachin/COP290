#include "Player.cpp"
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;


class Enemy : public Gamer{

private: 

    string id;

    int currstate;
    int prevstate;

    bool moving=false;
    int pr[4]={4,3,1,2};
    int currDir=3;
    int nextDir=0;

public: 

    Enemy(Texture *enemyTex,string s){
        texture = enemyTex;
        sprite = new Sprites(enemyTex);
        id=s;
        currstate = 1;
        prevstate = 1;
    }

    ~Enemy(){
        Gamer::free();
    }

    void setState(int s) {currstate = s;}


    void movement(Map *map,Player* P) {
        dirConfig(currDir,false);
        int currX = currTile->getX();
        int currY = currTile->getY();
        int nextX = currX;
        int nextY = currY;

        int temp1=currX+1;
        int temp2=currY+1;
        int temp3=currY-1;
        int temp4=currX-1;

        handleBound(temp1,xBound);
        handleBound(temp2,yBound);
        handleBound(temp3,yBound);
        handleBound(temp4,xBound);

        int nextXX[4]={temp1,currX,currX,temp4};
        int nextYY[4]={currY,temp2,temp3,currY};
        //frightened state
        if (currstate==0){
            if (prevstate==0){
                int i=rand()%4;
                while(true) {
                    if (i!=3-currDir){
                        nextX=nextXX[i];
                        nextY=nextYY[i];
                        nextTile=map->getTile(nextX,nextY);
                        if (nextTile!=NULL && nextTile->getBrick()== false){
                            currTile = nextTile;
                            nextTile = NULL;
                            animating=true;
                            nextDir=i;
                            break;
                        }
                    }
                    i++;
                    handleBound(i,4);
                }
            }
            else{
                int i=3-currDir;
                nextX=nextXX[i];
                nextY=nextYY[i];
                nextTile=map->getTile(nextX,nextY);
                if (nextTile!=NULL && nextTile->getBrick()== false){
                    currTile = nextTile;
                    nextTile = NULL;
                    animating=true;
                    nextDir=i;       
                }
            }
        }
        //scatter
        else if (currstate==1){
            nextDir= nextDirg(map->getTile(23,1),nextXX,nextYY,map);
            nextX=nextXX[nextDir];
            nextY=nextYY[nextDir];                
            nextTile=map->getTile(nextX,nextY);
            currTile = nextTile;
            nextTile = NULL;
            animating=true;       
        }
        // else if (currstate==2){

        //     vector<Tile*> path=calcRoute(currTile,P->getcurrTile(),map);
        //     nextTile=path[1];
        //     int a=currTile->getX()-nextTile->getX();
        //     int b=currTile->getY()-nextTile->getY();
        //     if (a==-1){
        //         nextDir=0;
        //     }
        //     else if (a==1){
        //         nextDir=3;
        //     }
        //     else if (b==-1){
        //         nextDir=1;
        //     }
        //     else if (b==1){
        //         nextDir=2;
        //     }
        //     currTile=nextTile;
        //     nextTile=NULL;
        // }
        dirConfig(nextDir,true);
    }

    void update( Map *map,Player* P) {


        if (animating) {
            spend = SDL_GetTicks() - start;

            if (FRAME_DELAY*SPEED <= spend) {
                animating = false;
            }
        }

        else  {
            if (visible) {
                start = SDL_GetTicks();
                movement(map,P);
            }
        }
    }

    vector<int> priorty(){
        //setting priorities in movement
        vector<int> arr;
        if (id=="blinky"){
            arr={0,2,3,1};
        }
        else if (id=="pinky"){
            arr={0,1,3,2};
        }
        else if (id=="inky"){
            arr={3,1,0,2};
        }
        else if (id=="clyde"){
            arr={3,2,0,1};
        }
        return arr;
    }


    int nextDirg(Tile* Target,int X[],int Y[],Map* map){
        int a=Target->getX();
        int b=Target->getY();
        int dir;
        double minn=INFINITY;
        for(int i=0;i<4;i++){              
            nextTile=map->getTile(X[i],Y[i]);      
            if (nextTile!=NULL && nextTile->getBrick()== false && i!=3-currDir){
                if (minn>distance(a,X[i],b,Y[i])){
                    minn=distance(a,X[i],b,Y[i]);
                    dir=i;
                }
                else if (minn=distance(a,X[i],b,Y[i])){
                    if (pr[i]<pr[dir]){
                        dir=i;
                    }
                }
            }          
        }
        return dir;
    }

    double distance(int a,int b,int c,int d){
        return sqrt((double)((a-b)*(a-b)+(c-d)*(c-d)));
    }


    void dirConfig(int& Dir, bool flag){
        if (flag){
            if (Dir==0){
                Dir=4;
            }
        }
        else {
            if (Dir==4){
                Dir=0;
            }
        }
    }
};