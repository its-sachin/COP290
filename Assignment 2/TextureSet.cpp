#include "Texture.cpp"
#include <unordered_map>

class TextureSet{

private:

    unordered_map<string, Texture*> Texturehash;


public:

    static SDL_Renderer *renderer;

    TextureSet(string path) {

        int numOfEntity = 9;
        string gameEntity[numOfEntity] = {"player1", "player2", "blinky", "pinky", "inky", "clyde", "brick", "coin", "bg"};

        for (int i=0; i< numOfEntity; i++) {

            Texture curr;
            bool isDone = curr.Load(path+gameEntity[i]+"bpm", renderer);
            if (isDone) {
                Texturehash[gameEntity[i]] = curr.getTexture();
            }
        }
    }

    Texture* getTexture(string object) {
        try {
            Texture* out = Texturehash.at(object);
            return out;
        } 
    
        catch(const out_of_range &e){
            return NULL;
        } 
    }

    void Free() {
        for (auto &it : Texturehash) {
            delete it.second;
            Texturehash.erase(it.first);
        }
    }
};