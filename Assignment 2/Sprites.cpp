#include "Map.cpp"

class Sprites{

private:
    Texture *mtexture;
    SDL_Rect Rectviews[5];

    //0-front
    //1-down
    //2-up
    //3-left
    //4-right

    void setSize(int width, int height) {
        
        for (int i =0; i < 5; i++) {
            Rectviews[i].w = width;
            Rectviews[i].h = height;
        }
    }

    void setDimen(int index, int x, int y) {
        Rectviews[index].x = x;
        Rectviews[index].y = y;
    }

public:

    Sprites(Texture *texture) {
        mtexture = texture;

        setSize(25,25);
        setDimen(0,0,50);
        setDimen(1,50,0);
        setDimen(2,50,25);
        setDimen(3,0,0);
        setDimen(4,0,25);

    }

    ~Sprites() {
        mtexture = NULL;
    }

    SDL_Rect *getRect(int index) {return &Rectviews[index]; }


};