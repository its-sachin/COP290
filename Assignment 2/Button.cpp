#include "Enemy.cpp"


class Button{

private:
    SDL_Point position;
    Texture *texture;
    Texture font;
    bool selected = false;
    bool changed = false;
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
        selected = false;
        changed = false;
        font.free();
    }

    bool isSelected() {return selected;} 

    void deselect() {
        selected = false;
        changed = false;
    }

    void setDimen(int w, int h) {
        width = w;
        height = h;
    }

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
            if (changed) {

                if (e->type == SDL_MOUSEBUTTONUP) {
                    selected = true;
                    changed = false;
                }

            }
            else if ( e->type == SDL_MOUSEBUTTONDOWN){

                changed = true;
            }
        }
        texture->renderWM(position.x,position.y);
        font.renderWM(position.x+20,position.y+7);
    }

    void handleEventWT(SDL_Event *e, SDL_Rect *clip =NULL) {

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
        texture->renderWM(position.x,position.y,clip);

    }

    void renderOT() {
        font.renderWM(position.x+20,position.y+7);
    }

};