#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;


class Texture{

private:

    SDL_Texture *texture = NULL;
    int height;
    int width;


public:

    SDL_Texture* getTexture() {return texture;}

    bool Load(string image, SDL_Renderer *renderer) {

        if (renderer == NULL) {
            cout << "Trying to load texture on null renderer" << endl;
            return false;
        }
        SDL_Surface *surface = SDL_LoadBMP(image.c_str());

        if (surface == NULL) {
            cout<< "Failed to load image " << image << " Error: " << SDL_GetError() << endl;
            return false;
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == NULL) {
            cout << "Failed to create texture from surface! Error: " << SDL_GetError() << endl;
            return false;
        }

        width = surface->w;
        height= surface->h;

        cout << "width " << width << endl;
        cout << "height " << height << endl;
        return true;

    }

    bool Draw(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flag = SDL_FLIP_NONE){

        if (renderer == NULL) {
            return false;
        }

        SDL_Rect source = {0,0,width,height};
        SDL_Rect dest = {x,y,width,height};

        SDL_RenderCopyEx(renderer,texture, &source, &dest, 0.0, NULL, flag);
        return true;
    }

    void remove() {
        delete texture;
    }

};