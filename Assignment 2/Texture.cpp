#include "Game.cpp"

class Texture{

private:

    SDL_Texture *texture;
    int height;
    int width;


public:

    SDL_Texture* getTexture() {return texture;}

    Texture() {
        texture = NULL;
        height = 0;
        width = 0;
    }

    ~Texture() {
        free();
    }

    int getHeight() {return height;}
    int getWidth() {return width;}

    bool Load(string image) {

        free();

        SDL_Texture* temp = NULL;

        SDL_Surface *surface = IMG_Load(image.c_str());

        if (surface == NULL) {

            cout << "Not able to load image " << image << " Error: " << SDL_GetError() << endl;
            return false;
        }

        temp = SDL_CreateTextureFromSurface(renderer, surface);

        if (temp == NULL) {

            cout << "Not able to create texture from " << image << " Error: " << SDL_GetError() << endl;
            SDL_FreeSurface(surface);
            return false;
        }

        width = surface->w;
        height = surface->h;
        SDL_FreeSurface(surface);

        texture = temp;
        return true;

    }

    void render(int x, int y) {
        if (renderer == NULL){
            cout << "Cant render on NULL renderer" << endl;
            return;
        }
        SDL_Rect dest = {x,y,width,height};
        SDL_RenderCopy(renderer, texture, NULL,&dest);
    }

    void render(int x, int y, SDL_Rect *clip) {

        if (renderer == NULL){
            cout << "Cant render on NULL renderer" << endl;
            return;
        }
        SDL_Rect dest = {x,y,width,height};

        if (clip != NULL) {
            dest.w = clip->w;
            dest.h = clip->h;
        }
        SDL_RenderCopy(renderer, texture, clip,&dest);
    }

    void free() {

        if (texture != NULL) {
            SDL_DestroyTexture(texture);

            texture = NULL;
            height = 0;
            width = 0;

        }
    }

};