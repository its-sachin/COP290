#include "Map.cpp"

class Sprites{

private:
    Texture *mtexture;
    SDL_Rect Rectviews[3][2];

    //00-leftfront
    //01-rightfront
    //10-leftdown
    //11-rightdown
    //20-leftup
    //21-rightup

    void setSize(int width, int height) {
        
        for (int i =0; i < 3; i++) {

            for (int j=0; j<2; j++ ){
                Rectviews[i][j].w = width;
                Rectviews[i][j].h = height;

                Rectviews[i][j].x = j*width;
                Rectviews[i][j].y = i*height;
            }
        }
    }


public:

    Sprites(Texture *texture) {
        mtexture = texture;

        setSize(25,25);
        

    }

    ~Sprites() {
        mtexture = NULL;
    }

    SDL_Rect *getRect(int UD, int LR) {return &Rectviews[UD][LR]; }


};