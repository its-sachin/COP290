#include "Enemy.cpp"


class Button{

private:
    SDL_Point position;
    Texture *texture;
    Texture font;
    bool selected = false;
    int width;
    int height;

public:

    Button(int x, int y,Texture *t){
        position = {x,y};
        width = t->getWidth();
        height = t->getHeight();
        texture = t;
    }

    ~Button(){

        width = 0;
        height = 0;
        texture = NULL;
        font.free();
    }

    bool isSelected() {return selected;} 

    Texture *getFont() {
        return &font;
    }

    void handleEvent( SDL_Event* e){

            int x, y;
            SDL_GetMouseState( &x, &y );

            if( x < position.x ||  x > position.x + width || y < position.y || y > position.y + height){

                texture->setAlpha(175);
            }

            else{

                texture->setAlpha(255);
                if ( e->type == SDL_MOUSEBUTTONDOWN){

                    selected = true;
                }
            }
            texture->renderWM(position.x,position.y);
            font.renderWM(position.x+20,position.y+7);
    }

};