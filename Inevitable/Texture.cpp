#include "Game.cpp"
#include <SDL2/SDL_ttf.h>

class Texture{

protected:

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

            cout << "Not able to load image " << image << " Error: " << IMG_GetError() << endl;
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

    bool Load(string text, TTF_Font *font, SDL_Colour colour) {

        free();

        // SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), colour);
        SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), colour, 500);
        if (surface == NULL) {
            cout << "Not able to load text surface Error: " << TTF_GetError() << endl;
            return false;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture == NULL) {

            cout << "Not able to create texture from text: " << text << " Error: " << SDL_GetError() << endl;
            SDL_FreeSurface(surface);
            return false;
        }

        width = surface->w;
        height = surface->h;
        SDL_FreeSurface(surface);
        return true;
    }

    void renderWM(int x, int y, SDL_Rect *clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        if (renderer == NULL){
            cout << "Cant render on NULL renderer" << endl;
            return;
        }
        SDL_Rect dest = {x,y,width,height};
        if (clip != NULL) {
            dest.w = clip->w;
            dest.h = clip->h;
        }
        SDL_RenderCopyEx(renderer, texture, clip,&dest, 0.0, NULL, flip);
    }

    void render(int x, int y, SDL_Rect *clip = NULL) {

        if (renderer == NULL){
            cout << "Cant render on NULL renderer" << endl;
            return;
        }
        SDL_Rect dest = {x+X_MARGIN,y+Y_MARGIN,width,height};

        if (clip != NULL) {
            dest.w = clip->w;
            dest.h = clip->h;
        }
        SDL_RenderCopy(renderer, texture, clip,&dest);
    }

    void setAlpha( Uint8 alpha ){

        SDL_SetTextureAlphaMod( texture, alpha );
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