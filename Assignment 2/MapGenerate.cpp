#include "Tile.cpp"
#include <ctime>
#include <stack>
#include <fstream>

class Block {

private:

    char type = 'x';
    bool visited = false;


    bool top = true;
    bool bottom = true;
    bool left = true;
    bool right = true;

public:

    void setType(char newType) {
        type = newType;
    }

    void setVisited() {
        visited =true;
    } 

    void unsetTop() {
        top = false;
    }

    void unsetBottom() {
        bottom = false;
    }

    void unsetLeft() {
        left = false;
    }

    void unsetRight() {
        right = false;
    }

    bool isVisited() {return visited;}
    char getType() {return type;}
    bool isTop() {return top;}
    bool isBottom() {return bottom;}
    bool isLeft() {return left;}
    bool isRight() {return right;}
};

class MapGenerate {

private:

    int MAX_COIN = 256;
    bool playerselected = false;
    bool bselected = false;
    bool nselected = false;
    bool hselected = false;
    bool cselected = false;
    bool iselected = false;
    int numCoins = 0;
    //0p 1b 2n 3h 4c 5i
    int store[6][2] = {-1}; 

    void initMap(Block Maze[DIMEN][DIMEN]) {

        for (int i=1; i< DIMEN -1; i++) {
            Maze[i][1].unsetLeft();
            Maze[i][DIMEN-2].unsetRight();
        }

        for (int i=1; i< DIMEN -1; i++) {
            Maze[1][i].unsetTop();
            Maze[DIMEN-2][i].unsetBottom();
        }
    }

    char isDone(int y, int x) {

        if (playerselected && y == store[0][0] && x == store[0][1]) {
            return 'p';
        }

        else if (bselected && y == store[1][0] && x == store[1][1]) {
            return 'b';
        }

        else if (nselected && y == store[2][0] && x == store[2][1]) {
            return 'n';
        }

        else if (hselected && y == store[3][0] && x == store[3][1]) {
            return 'h';
        }

        else if (cselected && y == store[4][0] && x == store[4][1]) {
            return 'c';
        }

        else if (iselected && y == store[5][0] && x == store[5][1]) {
            return 'i';
        }
        return ' ';

    }

    char addChar(int y, int x) {

        char curr = isDone(y,x);

        if (curr != ' ') {
            return curr;
        }

        if (!playerselected) {
            playerselected = true;
            store[0][0] = y;
            store[0][1] = x;
            return 'p';
        }

        if (abs(store[0][0]-y) > 8 || abs(store[0][1]-x) > 8) {
            if (!bselected) {
                bselected = true;
                store[1][0] = y;
                store[1][1] = x;
                return 'b';
            }
            else if (!nselected) {
                nselected = true;
                store[2][0] = y;
                store[2][1] = x;
                return 'n';
            }

            else if (!hselected) {
                hselected = true;
                store[3][0] = y;
                store[3][1] = x;
                return 'h';
            }

            else if (!cselected) {
                cselected = true;
                store[4][0] = y;
                store[4][1] = x;
                return 'c';
            }
            else if (!iselected) {
                iselected = true;
                store[5][0] = y;
                store[5][1] = x;
                return 'i';
            }
        }

        if (numCoins < MAX_COIN) {
            
            int choice = rand()%(DIMEN*DIMEN);

            if (choice > ((DIMEN-1)*(DIMEN-1))) {
                return ' ';
            }

            numCoins += 1;
            return '.';

        } 

        return ' ';

    }

    void DFS(Block Maze[DIMEN][DIMEN]) {
        srand((unsigned)time(NULL)); 

        int n = (DIMEN-1)*(DIMEN-1)/4; 
        int x = abs((2*rand()+1)%(DIMEN-1));
        int y = abs((2*rand()+1)%(DIMEN-1));

        Maze[x][y].setType('x');
        Maze[x][y].setVisited();

        int covered = 1;

        stack<pair<int,int>> s;

        while(covered < n) {

            bool a = !Maze[y-2][x].isVisited() && Maze[y][x].isTop() && Maze[y-2][x].isBottom();
            bool b = !Maze[y+2][x].isVisited() && Maze[y][x].isBottom() && Maze[y+2][x].isTop();
            bool c = !Maze[y][x-2].isVisited() && Maze[y][x].isLeft() && Maze[y][x-2].isRight();
            bool d = !Maze[y][x+2].isVisited() && Maze[y][x].isRight() && Maze[y][x+2].isLeft();

            if (a||b||c||d) {

                int choice = (rand()%4) +1;

                switch (choice)
                {
                case 1:
                    if (y>1) {
                        if (!Maze[y-2][x].isVisited()){

                            s.push({x,y});
                            covered += 1;

                            Maze[y][x].unsetTop();
                            Maze[y-1][x].setVisited();
                            Maze[y-1][x].setType(addChar(y-1,x));

                            y -=2;

                            Maze[y][x].setVisited();
                            Maze[y][x].setType(addChar(y,x));
                            Maze[y][x].unsetBottom();

                        }

                        else {
                            continue;
                        }
                    }
                    break;

                case 2:
                    if (y<DIMEN-2) {
                        if (!Maze[y+2][x].isVisited()){

                            s.push({x,y});
                            covered += 1;

                            Maze[y][x].unsetBottom();
                            Maze[y+1][x].setVisited();
                            Maze[y+1][x].setType(addChar(y+1,x));

                            y +=2;

                            Maze[y][x].setVisited();
                            Maze[y][x].setType(addChar(y,x));
                            Maze[y][x].unsetTop();


                        }

                        else {
                            continue;
                        }
                    }
                    break;

                case 3:
                    if (x>1) {
                        if (!Maze[y][x-2].isVisited()){

                            s.push({x,y});
                            covered += 1;

                            Maze[y][x].unsetLeft();
                            Maze[y][x-1].setVisited();
                            Maze[y][x-1].setType(addChar(y,x-1));

                            x -=2;

                            Maze[y][x].setVisited();
                            Maze[y][x].setType(addChar(y,x));
                            Maze[y][x].unsetRight();

                        }

                        else {
                            continue;
                        }
                    }
                    break;
                
                case 4:
                    if (x<DIMEN-2) {
                        if (!Maze[y][x+2].isVisited()){

                            s.push({x,y});
                            covered += 1;

                            Maze[y][x].unsetRight();
                            Maze[y][x+1].setVisited();
                            Maze[y][x+1].setType(addChar(y,x+1));

                            x +=2;

                            Maze[y][x].setVisited();
                            Maze[y][x].setType(addChar(y,x));
                            Maze[y][x].unsetLeft();

                        }

                        else {
                            continue;
                        }
                    }
                    break;
                
                default:
                    break;
                }
            }

            else {
                pair<int,int> temp = s.top();
                x = temp.first;
                y = temp.second;

                s.pop();
                
            }

        }

        Maze[y][x].setType(addChar(y,x));

    }

public:

    void drawMap() {

        Block Maze[DIMEN][DIMEN];

        initMap(Maze);
        DFS(Maze);

        ofstream myfile; 

        myfile.open(MAPS_PATH + "/random.txt");

        for (int i = 0; i < DIMEN; i++) {
            if (i != 0) {
                myfile<<endl;
            }
            for (int j = 0; j < DIMEN; j++) {
                myfile << Maze[i][j].getType();
            }
        }

        myfile << " " << endl;

    }
};