#include "Texture.cpp"
#include <unordered_map>

class TextureSet{

private:

    unordered_map<string, Texture*> Texturehash;


public:

    TextureSet(string path) {
        //initialise
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