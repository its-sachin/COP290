#include "Player.cpp"
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;


class Enemy{

private: 
    int speed=2;

    int xbound;
    int ybound;
    string id;

    bool visible=true;

    int currstate;
    int prevstate;

    bool animating=false;

    bool moving=false;

    int currdirection=-1;

    Tile *currTile=NULL;
    Tile *nextTile=NULL;
    Texture *texture=NULL;

    void handleBound(int &x, int bound) {
    if (x >= bound) {
            x = x%bound;
        }
        
    else if (x < 0) {
            x = (x+bound)%bound;
        }
    }
public: 

    Enemy(Texture *enemyTex,string s){
        texture = enemyTex;
        id=s;
    }

    ~Enemy(){
        currTile=NULL;
        nextTile=NULL;
        texture=NULL;
    }
    void setInitTile(Tile* initTile) {
        currTile = initTile;
        nextTile = NULL;
    }

    void setBounds(int height, int width) {
        xbound = width;
        ybound = height;
    }
    void setSpeed(int s) {speed = s;}
    void setState(int s) {currstate = s;}
    bool isAnimating() {return animating;}


    void movement(Map *map,Player* P) {
        int currX = currTile->getX();
        int currY = currTile->getY();
        int nextX = currX;
        int nextY = currY;

        int temp1=currX+1;
        int temp2=currY+1;
        int temp3=currY-1;
        int temp4=currX-1;

        handleBound(temp1,xbound);
        handleBound(temp2,ybound);
        handleBound(temp3,ybound);
        handleBound(temp4,xbound);

        int nextXX[4]={temp1,currX,currX,temp4};
        int nextYY[4]={currY,temp2,temp3,currY};
        //frightened state
        if (currstate==0){
            if (prevstate==0){
                int i=rand()%4;
                while(true) {
                    if (i!=3-currdirection){
                        nextX=nextXX[i];
                        nextY=nextYY[i];
                        nextTile=map->getTile(nextX,nextY);
                        if (nextTile!=NULL && nextTile->getBrick()== false){
                            currTile = nextTile;
                            nextTile = NULL;
                            animating=true;
                            currdirection=i;
                            break;
                        }
                    }
                    i++;
                    handleBound(i,4);
                }
            }
            else{
                int i=3-currdirection;
                nextX=nextXX[i];
                nextY=nextYY[i];
                nextTile=map->getTile(nextX,nextY);
                if (nextTile!=NULL && nextTile->getBrick()== false){
                    currTile = nextTile;
                    nextTile = NULL;
                    animating=true;
                    currdirection=i;       
                }
            }
        }
        //scatter
        else if (currstate==1){
            vector<int> arr= priorty();
            int j=0;
            while (true){
                int i=arr[j];
                nextX=nextXX[i];
                nextY=nextYY[i];
                nextTile=map->getTile(nextX,nextY);
                if (nextTile!=NULL && nextTile->getBrick()== false){
                    currTile = nextTile;
                    nextTile = NULL;
                    animating=true;
                    currdirection=i;
                    break;
                }
                j++;
                handleBound(j,4);               
            }
        }
        else if (currstate==2){

            vector<Tile*> path=calcRoute(currTile,P->getcurrTile(),map);
            nextTile=path[1];
            int a=currTile->getX()-nextTile->getX();
            int b=currTile->getY()-nextTile->getY();
            if (a==-1){
                currdirection=0;
            }
            else if (a==1){
                currdirection=3;
            }
            else if (b==-1){
                currdirection=1;
            }
            else if (b==1){
                currdirection=2;
            }
            currTile=nextTile;
            nextTile=NULL;
        }
    }

    void update( Map *map,Player* P) {

        if (animating) {

        }

        else  {
            if (visible) {
                movement(map,P);
            }
        }
    }

    void render(int tileWidth, int tileHeight) {

        SDL_Rect src = {0,0,25,25};

        texture->render(currTile->getX()*tileWidth,currTile->getY()*tileHeight,&src);
    }

    vector<int> priorty(){
        //setting priorities in movement
        vector<int> arr;
        if (id=="blinky"){
            arr={0,1,3,2};
        }
        else if (id=="pinky"){
            arr={0,2,3,1};
        }
        else if (id=="inky"){
            arr={3,1,0,2};
        }
        else if (id=="clyde"){
            arr={3,2,0,1};
        }
        return arr;
    }


    template<typename T, typename priority_t>
    struct PriorityQueue {
        typedef pair<priority_t, T> PQElement;
        priority_queue<PQElement, vector<PQElement>,
            std::greater<PQElement >> elements;

        inline bool empty() const { return elements.empty(); }

        inline void put(T item, priority_t priority) {
            elements.emplace(priority, item);
        }

        inline T get() {
            T best_item = elements.top().second;
            elements.pop();
            return best_item;
        }
    };

    vector<Tile*> calcRoute(Tile* start,Tile* goal,Map* m){
        unordered_map<Tile*, Tile*> came_from;		
        unordered_map<Tile*, int> cost_so_far;
        PriorityQueue<Tile*,int> pathf;
        came_from[start] = start;
        cost_so_far[start] = 0;

        pathf.put(start, 0);
        while (!pathf.empty())
        {
            Tile* current = pathf.get();
            if (current == goal)
                break;
            Tile* neigbour[4]={m->getTile(current->getX()+1,current->getY()),m->getTile(current->getX()-1,current->getY()-1),m->getTile(current->getX(),current->getY()+1),m->getTile(current->getX(),current->getY()-1)};
            Tile* next;
            for (int i=0;i++;i<4) {
                next=neigbour[i];
                int new_cost = cost_so_far[current] + 1;

                if (next != NULL && (!cost_so_far.count(next) || new_cost < cost_so_far[next]))
                {
                    // If there's a wall in the tile, set cost of movement to INFINITY
                    // TODO: We shouldn't include those tiles at all!
                    if (next->getBrick()) new_cost = INFINITY;

                    cost_so_far[next] = new_cost;
                    int priority = new_cost + Heuristic(next, goal);
                    pathf.put(next, priority);
                    came_from[next] = current;
                }
            }
        }

        vector<Tile*> path;
        Tile* current = goal;

        path.push_back(current);

        // Add all tiles of the path to a list
        while (current != start)
        {
            current = came_from[current];
            path.push_back(current);
        }

        // Reverse the list, so that we start at the beginning
        reverse(path.begin(), path.end());

        return path;
    }

    inline int Heuristic(Tile* a, Tile* b)
    {
        return abs(a->getX() - b->getX()) + abs(a->getY() - b->getY());
    }

};