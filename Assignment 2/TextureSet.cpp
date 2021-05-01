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
    logoTex,
    movableBG,
    sciTex,
    sparkTex,
    modeTex,
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

        
        player1Tex.Load(path + "/" + "player1.png");
        player2Tex.Load(path + "/" + "player2.png");
        blinkyTex.Load(path + "/" + "blinky.png");
        pinkyTex.Load(path + "/" + "pinky.png");
        inkyTex.Load(path + "/" + "inky.png");
        clydeTex.Load(path + "/" + "clyde.png");
        brickTex.Load(path + "/" + "brick.jpg");
        coinTex.Load(path + "/" + "coin.png");
        frightTex.Load(path + "/" + "frightened.png");
        dieTex.Load(path + "/" + "die.png");
        scoreBackTex.Load(path + "/" + "scoreUI.png");
        gameTex.Load(path + "/gamePhoto.png");
        logoTex.Load(path + "/logo.bmp");
        movableBG.Load(path + "/back.jpg");
        modeTex.Load(path + "/mode.png");
    }

    void loadWord(Texture *texture,string word) {
        texture->Load(word,font,textColour);
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
        logoTex.free();
        modeTex.free();

        TTF_CloseFont(font);
        TTF_Quit();

    }
};