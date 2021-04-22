#include "Texture.cpp"

class TextureSet{

protected:


    Texture player1,player2,blinky,pinky, inky, clyde, brick, coin;


public:


    void loadTex(string path) {

        
        player1.Load(path + "/" + "player1.bmp");
        player2.Load(path + "/" + "player2.bmp");
        blinky.Load(path + "/" + "blinky.bmp");
        pinky.Load(path + "/" + "pinky.bmp");
        inky.Load(path + "/" + "inky.bmp");
        clyde.Load(path + "/" + "clyde.bmp");
        brick.Load(path + "/" + "brick.bmp");
        coin.Load(path + "/" + "coin.bmp");
    }

    void freeTex() {
        player1.free();
        player2.free();
        blinky.free();
        pinky.free();
        inky.free();
        clyde.free();
        brick.free();
        coin.free();
    }
};