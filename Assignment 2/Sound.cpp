//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "constants.hpp"

class Sound {

private:

    Mix_Music *bgm = NULL;

    Mix_Chunk *coin = NULL;
    Mix_Chunk *die = NULL;
    Mix_Chunk *respawn = NULL;
    Mix_Chunk *eat = NULL;
    Mix_Chunk *mind = NULL;

    bool success = true;


public:

    Sound(){

        if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            cout << "SDL Audio could not be initialised! Error: " << SDL_GetError() << endl;
            success = false;
        }

        bgm = Mix_LoadMUS((SOUND_PATH + "/bgm.mp3").c_str());
        if (bgm == NULL) {
            cout << "Failed to load BGM! Error: " << Mix_GetError() << endl;
        }

        string name = "coin";

        coin = Mix_LoadWAV( (SOUND_PATH + "/" + name + ".wav").c_str() );
        if( coin == NULL )
        {
            cout<< "Failed to load " << name << " sound effect! Error: " << Mix_GetError() << endl;
        }

        name = "die";

        die = Mix_LoadWAV( (SOUND_PATH + "/" + name + ".wav").c_str() );
        if( die == NULL )
        {
            cout<< "Failed to load " << name << " sound effect! Error: " << Mix_GetError() << endl;
        }

        name = "respawn";

        respawn = Mix_LoadWAV( (SOUND_PATH + "/" + name + ".wav").c_str() );
        if( respawn == NULL )
        {
            cout<< "Failed to load " << name << " sound effect! Error: " << Mix_GetError() << endl;
        }

        name = "eat";

        eat = Mix_LoadWAV( (SOUND_PATH + "/" + name + ".wav").c_str() );
        if( eat == NULL )
        {
            cout<< "Failed to load " << name << " sound effect! Error: " << Mix_GetError() << endl;
        }

        name = "mind";

        mind = Mix_LoadWAV( (SOUND_PATH + "/" + name + ".wav").c_str() );
        if( mind == NULL )
        {
            cout<< "Failed to load " << name << " sound effect! Error: " << Mix_GetError() << endl;
        }
    

    }


    ~Sound() {

        Mix_FreeMusic(bgm);
        Mix_FreeChunk(die);
        Mix_FreeChunk(eat);
        Mix_FreeChunk(respawn);
        Mix_FreeChunk(coin);
        Mix_FreeChunk(mind);
        bgm = NULL;
        coin = NULL;
        die = NULL;
        respawn = NULL;
        eat = NULL;
        mind = NULL;

        Mix_Quit();
    }

    void playEat() {
        if (eat != NULL) {
            Mix_PlayChannel( -1, eat, 0 );
        }
    }

    void playDie() {
        if (die != NULL) {
            Mix_PlayChannel( -1, die, 0 );
        }
    }

    void playRespawn() {
        if (respawn != NULL) {
            Mix_PlayChannel( -1, respawn, 0 );
        }
    }

    void playCoin() {
        if (coin != NULL) {
            Mix_PlayChannel( -1, coin, 0 );
        }
    }

    void playMind() {
        if (mind != NULL) {
            Mix_PlayChannel( -1, mind, 0 );
        }
    }

    void startBGM() {

        if (bgm != NULL) {

            if( Mix_PlayingMusic() == 0 ){
                
                Mix_PlayMusic(bgm, -1 );
            }

            else{

                if( Mix_PausedMusic() == 1 ){
                    Mix_ResumeMusic();
                }
                else{
                    Mix_PauseMusic();
                }
            }
        }
    }

    void stopBGM() {
        Mix_HaltMusic();
    }


};