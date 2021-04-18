#include "Game.cpp"
#include "Player.cpp"
#include "Enemy.cpp"

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;


class Pacman: public Game{
    private:
    Player Thanos;
    Enemy Blinky;
    Enemy Pinky;
    Enemy Inky ;
    Enemy Clyde;

    public:
    void render(){
        SDL_RenderClear(renderer);
        // doBetween;
        SDL_RenderPresent(renderer);
    }

};