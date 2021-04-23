#include "Texture.cpp"


class TextureSet{

protected:


    Texture player1Tex,
    player2Tex,
    blinkyTex,
    pinkyTex, 
    inkyTex, 
    clydeTex, 
    brickTex, 
    coinTex, 
    frightTex, 
    dieTex, 
    score1Tex,
    score2Tex,
    gameTex,
    menuFont,
    logoTex,
    scoreBackTex;

    TTF_Font *font = NULL;
    SDL_Color textColour = { 255, 255, 255 };
    bool success = true;

public:


    void loadTex(string path) {

        if( TTF_Init() == -1){
            cout<< "SDL_ttf could not initialize! Error: "<< TTF_GetError << endl;
            success = false;
        }
        else {
            font = TTF_OpenFont((TEXT_PATH + "/Sportrop.otf").c_str(), TEXT_SIZE);

            if (font == NULL) {
                cout << "Font could not be initialised! Error "<< TTF_GetError() << endl;
                success = false;
            }
        }

        
        player1Tex.Load(path + "/" + "player1.bmp");
        player2Tex.Load(path + "/" + "player2.bmp");
        blinkyTex.Load(path + "/" + "blinky.bmp");
        pinkyTex.Load(path + "/" + "pinky.bmp");
        inkyTex.Load(path + "/" + "inky.bmp");
        clydeTex.Load(path + "/" + "clyde.bmp");
        brickTex.Load(path + "/" + "brick.bmp");
        coinTex.Load(path + "/" + "coin.bmp");
        frightTex.Load(path + "/" + "frightened.bmp");
        dieTex.Load(path + "/" + "die.bmp");
        scoreBackTex.Load(path + "/" + "scoreUI.jpg");
        gameTex.Load(path + "/gamePhoto.png");
        logoTex.Load(path + "/logo.bmp");
        menuFont.Load("      --Select Mode--\n   Single Player [Press s]\nTwo Player Online [Press o]\nTwo Player Offline [Press d]",font,textColour);
    }

    void renderScore1(int score, int x, int y) {
        if (success) {
            score1Tex.Load(to_string(score), font, textColour);
            score1Tex.renderWM(x,y);
        }
    }

    void renderScore2(int score, int x, int y) {
        if (success) {
            score2Tex.Load(to_string(score),font, textColour);
            score2Tex.renderWM(x,y);
        }
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
        frightTex.free();
        dieTex.free();
        scoreBackTex.free();
        score1Tex.free();
        score2Tex.free();
        gameTex.free();
        menuFont.free();
        logoTex.free();

        TTF_CloseFont(font);
        TTF_Quit();

    }
};