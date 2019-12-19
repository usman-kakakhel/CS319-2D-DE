#include "MenuFrame.h"

MenuFrame::MenuFrame(){
    //create BG texture
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(bGSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);

    //finding the position of the bg
    int x = ((DisplayManager::SCREEN_WIDTH - mCTexture->mWidth)/2);
    bgPoint.setX(x);
    bgPoint.setY(0);
    initializeMenu();
}
MenuFrame::~MenuFrame(){
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
    if (newGame != NULL)
        delete newGame;
    if (resume != NULL)
        delete resume;
    if (shop != NULL)
        delete shop;
    if (quit != NULL)
        delete quit;
}

void MenuFrame::update(Point* pressPoint, GameState* state){
    
    //rendering background
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, bgPoint, {0,0}, NULL, 0, NULL, SDL_FLIP_NONE);
    //renderin the menu text
    Point pos;
    pos.setX(((DisplayManager::SCREEN_WIDTH - 230)/2));
    pos.setY(DisplayManager::SCREEN_HEIGHT / 9);
    DisplayManager::renderText("DEFENDER", pos);

    //render the buttons
    if (newGame != NULL)
        newGame->render();
    if (resume != NULL && *state == PAUSE)
        resume->render();
    if (shop != NULL && *state == PAUSE)
        shop->render();
    if (quit != NULL)
        quit->render();

    //check if any buttons are pressed
    if (newGame != NULL && newGame->isPressed(pressPoint)){
        *state = NEW_GAME;
    }
    if (resume != NULL && resume->isPressed(pressPoint) && *state == PAUSE){
        *state = RESUME;
    }
    if (shop != NULL && shop->isPressed(pressPoint) && *state == PAUSE){
        *state = SHOP;
    }
    if (quit != NULL && quit->isPressed(pressPoint)){
        *state = QUIT;
    }
}

void MenuFrame::initializeMenu(){
    Point pos;
    pos.setX(((DisplayManager::SCREEN_WIDTH - 360)/2));

    pos.setY(250);
    newGame = new Button(pos, "../resources/newGameButton.png");
    pos.setY(400);
    resume = new Button(pos, "../resources/resumeButton.png");
    pos.setY(550);
    shop = new Button(pos, "../resources/shopButton.png");
    pos.setY(700);
    quit = new Button(pos, "../resources/quitButton.png");

    // else if (*state == MAIN_MENU){
    //     pos.setY(400);
    //     newGame = new Button(pos, "../resources/newGameButton.png"); 
    //     pos.setY(700);
    //     quit = new Button(pos, "../resources/quitButton.png");
    // }
}