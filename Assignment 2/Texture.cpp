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
        // SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (texture == NULL) {
            cout << "Failed to create texture from surface! Error: " << SDL_GetError() << endl;
            return false;
        }

        width = surface->w;
        height= surface->h;

        return true;

    }

    bool Draw(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flag = SDL_FLIP_NONE){

        if (renderer == NULL) {
            return false;
        }

        SDL_Rect dest = {x,y,width,height};

        SDL_Texture* map_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 600, 800);
        SDL_SetRenderTarget(renderer, map_texture);

        SDL_RenderCopy(renderer,texture, NULL, &dest);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        return true;
    }

    void remove() {
        if (texture != NULL) {
            cout <<"";
            SDL_DestroyTexture(texture);
            texture = NULL;

            width = 0;
            height = 0;
        }
    }

};