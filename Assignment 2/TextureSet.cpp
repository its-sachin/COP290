#include "Texture.cpp"

class TextureSet{

protected:


    Texture player1Tex,player2Tex,blinkyTex,pinkyTex, inkyTex, clydeTex, brickTex, coinTex;


public:


    void loadTex(string path) {

        
        player1Tex.Load(path + "/" + "player1.bmp");
        player2Tex.Load(path + "/" + "player2.bmp");
        blinkyTex.Load(path + "/" + "blinky.bmp");
        pinkyTex.Load(path + "/" + "pinky.bmp");
        inkyTex.Load(path + "/" + "inky.bmp");
        clydeTex.Load(path + "/" + "clyde.bmp");
        brickTex.Load(path + "/" + "brick.bmp");
        coinTex.Load(path + "/" + "coin.bmp");
    }

    void freeTex() {
        player1Tex.free();
        player2Tex.free();
        blinkyTex.free();
        pinkyTex.free();
        inkyTex.free();
        clydeTex.free();
        brickTex.free();
        coinTex.free();
    }
};