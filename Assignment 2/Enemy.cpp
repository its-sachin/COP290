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
    int currDir=-1;
    int nextDir=0;

    int xCorner;
    int yCorner;
    int st=0;//timer for scatter
    int ct=0;//timer for chase 
    int stime[4]={7,7,5,5};//time for various levels 
    int ctime[4]={20,20,20,INFINITY};//chase time for various levels 
    int xHome;//x cordinate of home tile
    int yHome;//y cordinate of home tile 
    int levels=0;//level of the operation of enemy

public: 

    Enemy(Texture *enemyTex,string s){
        texture = enemyTex;
        sprite = new Sprites(enemyTex);
        id=s;
        currstate = 1;
        prevstate = -1;
    }

    ~Enemy(){
        Gamer::free();
    }

    void setState(int s) {currstate = s;}
    string getId() {return id;}
    void init(Map *map) {

        setBounds(map->getWidth(), map->getHeight());
        xHome=map->getHomeTile()->getX();
        yHome=map->getHomeTile()->getY();   

        if (id == "blinky") {
            setInitTile(map->getBlinkyInit());

            xCorner = xBound-2;
            yCorner = -2;
        }

        else if (id == "pinky") {
            setInitTile(map->getPinkyInit());

            xCorner = 1;
            yCorner = -2;
        }

        else if (id == "inky") {
            setInitTile(map->getInkyInit());

            xCorner = 0;
            yCorner = yBound;
            currDir = 1;
        }

        else if (id == "clyde") {
            setInitTile(map->getClydeInit());

            xCorner = xBound -1;
            yCorner = yBound;
            currDir = 1;
        }
    }


    void movement(Map *map,Player* P,Enemy* E) {
        dirConfig(currDir,false);
        updateState(P,map);
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
                else {
                    nextX=nextXX[currDir];
                    nextY=nextYY[currDir];
                    nextTile=map->getTile(nextX,nextY);  
                    nextTile=map->getTile(nextX,nextY);  
                    currTile = nextTile;
                    nextTile = NULL;
                    animating=true;
                    nextDir=currDir;                 
                }
            }
        }
        //scatter
        else if (currstate==1){
            nextDir= nextDirg(xCorner,yCorner,nextXX,nextYY,map);
            nextX=nextXX[nextDir];
            nextY=nextYY[nextDir];    
            nextTile=map->getTile(nextX,nextY);
            currTile = nextTile;
            nextTile = NULL;
            animating=true;       
        }
        //chase mode
        else if (currstate==2){
            if (prevstate!=2){
                nextDir=3-currDir;
            }
            else{
                vector<int> v= chhoseTarget(P,E,map);
                nextDir= nextDirg(v[0],v[1],nextXX,nextYY,map); 
            }
            nextX=nextXX[nextDir];
            nextY=nextYY[nextDir];    
            nextTile=map->getTile(nextX,nextY);
            currTile = nextTile;
            nextTile = NULL;
            animating=true;   

        }
        dirConfig(nextDir,true);
        currDir = nextDir;
        nextDir = 0;
    }

    void update( Map *map,Player* P,Enemy* E) {


        if (animating) {
            spend = SDL_GetTicks() - start;

            if (FRAME_DELAY*SPEED <= spend) {
                animating = false;
            }
        }

        else  {
            if (visible) {
                start = SDL_GetTicks();
                movement(map,P,E);
            }
        }
    }


    int nextDirg(int a, int b,int X[],int Y[],Map* map){
        int dir;
        double minn=INFINITY;
        for(int i=0;i<4;i++){              
            nextTile=map->getTile(X[i],Y[i]);      
            if (nextTile!=NULL && nextTile->getBrick()== false && i!=3-currDir){
                double dist = distance(a,X[i],b,Y[i]);
                if (minn>dist){
                    minn=dist;
                    dir=i;
                }
                else if (minn==dist){
                    if (pr[i]<pr[dir]){
                        dir=i;
                    }
                }
            }          
        }
        return dir;
    }

    double distance(int a,int b,int c,int d){
        return sqrt((double)(((a-b)*(a-b))+((c-d)*(c-d))));
    }

    vector<int> chhoseTarget(Player* P,Enemy* B,Map* map){
        int x= P->getcurrTile()->getX();
        int y= P->getcurrTile()->getY();

        int direction=P->getCurr();

        if (id=="blinky"){
            vector<int> v={x,y};
            return v;           
        }
        int x1=B->getcurrTile()->getX();
        int y1=B->getcurrTile()->getY();
        if (id=="pinky"){
            switch (direction){
                case 1:
                y=y+4;
                case 2:
                x=x-4;
                y=y-4;
                case 3:
                x=x-4;
                case 4:
                x=x+4;
            }
        }
        else if (id=="inky"){
            switch (direction){
                case 1:
                y=y+2;
                case 2:
                x=x-2;
                y=y-2;
                case 3:
                x=x-2;
                case 4:
                x=x+2;
            }
            inkyTile(x,y,x1,y1);
        }
        else {
            if (distance(x,currTile->getX(),y,currTile->getY())<8){
                x=xCorner;
                y=yCorner;
            }
        }
        handleBound(x,xBound);
        handleBound(y,yBound);
        vector<int> v={x,y};
        return v;
    }

    void inkyTile(int& a,int& b,int& c,int& d){
        a=a+(a-c);
        b=b+(b-d);
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


    void updateState(Player* P,Map* map){
        int state=currstate;
        if (P->getStone()=="mind") {
            if (P->getcurrTile()==this->getcurrTile()){
                state=3;       
            }
            else {
                state=0;
            }
        }
        else{
            if (currstate==3){
                if (this->getcurrTile()==map->getHomeTile()){
                    if (ctime!=0){
                        state=2;
                    }
                    else{
                        state=1;
                    }
                }
            }
            else if (currstate==1){
                cout<<st<<endl;
                st+=SDL_GetTicks()/1000;
                if (st==stime[levels]){
                    state=2;
                    st=0;
                }
            }
            else if (currstate==2){
                ct+=SDL_GetTicks()/1000;
                if (ct==ctime[levels]){
                    state=1;
                    ct=0;
                    levels++;
                }
            }
            if (P->getStone()== "mind"){
                if (P->getcurrTile()==this->getcurrTile()){
                    state=3;       
                }
                else {
                    state=0;
                }           
            }
        }
        prevstate=currstate;
        currstate=state;
    }
    void render() {

        SDL_Rect src = {0,0,TILE_WIDTH,TILE_HEIGHT};

        texture->render(currTile->getX()*TILE_WIDTH,currTile->getY()*TILE_HEIGHT,&src);
    }
};