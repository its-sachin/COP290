#include "Texture.cpp"
#include <unordered_map>

class TextureSet{

private:

    int numOfEntity = 8;

    Texture player1,player2,blinky,pinky, inky, clyde, brick, coin;

    unordered_map<string, Texture> hash = {{"player1",player1},{"player2",player2},{"blinky",blinky},{"pinky",pinky},{"inky",inky},{"clyde",clyde},{"brick",brick},{"coin",coin}};


public:


    TextureSet(string path) {

        
        for (auto& it: hash) {

            it.second.Load(path + "/" + it.first + ".bmp");
        }
    }

    Texture getTexture(string object) {
        return hash.at(object);
    }

    void render(string object, int x, int y) {
        hash.at(object).render(x,y);
    }

    ~TextureSet() {
        for (auto it = hash.cbegin(); it != hash.cend();) {
            it->second.~Texture();
            hash.erase(it++);
        }

        hash.clear();
    }
};