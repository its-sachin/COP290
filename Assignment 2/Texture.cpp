#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;


class Texture{

private:

    SDL_Texture *texture = NULL;


public:

    SDL_Texture* getTexture() {return texture;}

    bool Load(string image, SDL_Renderer *renderer) {

        if (renderer == NULL) {
            cout << "Trying to load texture on null renderer" << endl;
            return false;
        }
        SDL_Surface *surface = IMG_Load(image.c_str());

        if (surface == NULL) {
            cout<< "Failed to load image " << image << " Error: " << SDL_GetError() << endl;
            return false;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == NULL) {
            cout << "Failed to create texture from surface! Error: " << SDL_GetError() << endl;
            return false;
        }

    }

    void Draw(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_RendererFlip flag = SDL_FLIP_NONE){

        SDL_Rect source = {0,0,width,height};
        SDL_Rect dest = {x,y,width,height};

        SDL_RenderCopy(renderer,texture, &srcRect, &destRec,0,NULL, flag);
    }

};