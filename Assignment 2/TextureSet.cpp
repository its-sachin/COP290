#include "Texture.cpp"
#include <unordered_map>

class TextureSet{

private:

    unordered_map<string, Texture*> Texturehash;


public:


    TextureSet(string path, SDL_Renderer *renderer) {

        int numOfEntity = 9;
        string gameEntity[numOfEntity] = {"player1", "player2", "blinky", "pinky", "inky", "clyde", "brick", "coin", "bg"};

        for (int i=0; i< numOfEntity; i++) {

            Texture curr;
            bool isDone = curr.Load(path+"/" +gameEntity[i]+".bmp", renderer);
            if (isDone) {
                Texturehash[gameEntity[i]] = &curr;
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
            it.second->remove();
            delete it.second;
            Texturehash.erase(it.first);
        }

        Texturehash.clear();
    }
};