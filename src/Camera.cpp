#include "Camera.h"

Camera::Camera(){
    numOfHills = (DisplayManager::GAME_WIDTH / 808) + 1;
    backgroundPosStart = new Point[numOfHills];
    for (int i = 0; i < numOfHills; i++){
        Point a((i * 808), DisplayManager::SCREEN_HEIGHT  - 130);
        backgroundPosStart[i] = a;
    }

    //create textures of all images once
    mCTextureList = new DisplayManager::CustomTexture*[7];
    for (int i = 0; i < 7; i++){
        mCTextureList[i] = new DisplayManager::CustomTexture();
        DisplayManager::loadFromFile(spriteList[i], mCTextureList[i]->mTexture, mCTextureList[i]->mWidth, mCTextureList[i]->mHeight); 
    }
    mCTextureBG = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(background, mCTextureBG->mTexture, mCTextureBG->mWidth, mCTextureBG->mHeight);
    mCTextureGround = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(ground, mCTextureGround->mTexture, mCTextureGround->mWidth, mCTextureGround->mHeight);
    mCTextureGameOver = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(gOver, mCTextureGameOver->mTexture, mCTextureGameOver->mWidth, mCTextureGameOver->mHeight);

    Point a(1185, 10);
    mapView = new MapView(a);
}

Camera::~Camera(){
    if (mCTextureList != NULL){
        for (int i = 0; i < 7; i++){
            delete mCTextureList[i]->mTexture;
        }
        delete[] mCTextureList;
    }
    if (mCTextureBG != NULL){
        delete mCTextureBG->mTexture;
        delete mCTextureBG;
    }
    if (mCTextureGround != NULL){
        delete mCTextureGround->mTexture;
        delete mCTextureGround;
    }
    if (mCTextureGameOver != NULL){
        delete mCTextureGameOver->mTexture;
        delete mCTextureGameOver;
    }
    if (mapView != NULL)
        delete mapView;
    mapView = NULL;
}

Point Camera::getPoint(){
    return myPoint;
}

void Camera::setPoint(Point myPoint){
    Camera::myPoint = myPoint;
}


void Camera::showGameOver(){
    Point newPoint;
    newPoint.setX((DisplayManager::SCREEN_WIDTH/2) - (mCTextureGameOver->mWidth/2));
    newPoint.setY((DisplayManager::SCREEN_HEIGHT/2) - 100);
    DisplayManager::render(mCTextureGameOver->mTexture, mCTextureGameOver->mWidth, mCTextureGameOver->mHeight, newPoint, 0);
    string message = "Please Press Escape to go to main menu.";
    newPoint.setY(newPoint.getY() + mCTextureGameOver->mHeight + 100);
    newPoint.setX(newPoint.getX() - 300);
    DisplayManager::renderText(message, newPoint);
}

int offset(int num) {
        if(num <= 0) {
                return 30;
        }
        if((int)(floor(log10(num)) + 1) == 3) {
                return 0;
        }
        if((int)(floor(log10(num)) + 1) == 2) {
                return 10;
        }
        if((int)(floor(log10(num)) + 1) == 1) {
                return 30;
        }
}


void Camera::render(int health, int fuel, int coin, int score, int missileCountdown, int clearScreenCountdown){
    // Point backGroundRenderPos = getRenderPointFor(backgroundPos);
    // DisplayManager::render(gRenderer, "../resources/background.jpg", backGroundRenderPos.getX(), backGroundRenderPos.getY());
    //technically rendering the backgroud in the camera so the background does not change even though we are moving constantly
    DisplayManager::render(mCTextureBG->mTexture, mCTextureBG->mWidth, mCTextureBG->mHeight, 0, 0);
    
    //display the hills
    Point hillPoint(0, backgroundPosStart[0].getY());
    int  x = (myPoint.getX() / 808) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(mCTextureGround->mTexture, mCTextureGround->mWidth, mCTextureGround->mHeight, hillPoint, myPoint);
    x = ((myPoint.getX() / 808) + 1) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(mCTextureGround->mTexture, mCTextureGround->mWidth, mCTextureGround->mHeight, hillPoint, myPoint);
    x = ((myPoint.getX() / 808) + 2) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(mCTextureGround->mTexture, mCTextureGround->mWidth, mCTextureGround->mHeight, hillPoint, myPoint);
    x = ((myPoint.getX() / 808) + 3) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(mCTextureGround->mTexture, mCTextureGround->mWidth, mCTextureGround->mHeight, hillPoint, myPoint);

    //print UI
    Point disp;
    disp.setY(5);
    Point spriteDisp;
    spriteDisp.setY(15);
    for (int i = 0; i < 7; i++){
        disp.setX(disp.getX() + 130);
        // DisplayManager::render(gRenderer, "../resources/base.png", disp, 0);
        if (i == 6)
            spriteDisp.setY(0); 
        spriteDisp.setX(disp.getX() + 30);
        DisplayManager::render(mCTextureList[i]->mTexture, mCTextureList[i]->mWidth, mCTextureList[i]->mHeight, spriteDisp, 0);
    }
    //rendering texts for stats
    disp.setY(50);

    int temp = offset(health);
    disp.setX(130 + temp);
    DisplayManager::renderText(to_string(health), disp);
    disp.setX(disp.getX()-temp);

    temp = offset(fuel);
    disp.setX(disp.getX() + 130 + temp);
    DisplayManager::renderText(to_string(fuel), disp);
    disp.setX(disp.getX()-temp);

    temp = offset(coin);
    disp.setX(disp.getX() + 130 + temp + 10);
    DisplayManager::renderText(to_string(coin), disp);
    disp.setX(disp.getX()-temp-10);

    temp = offset(score);
    disp.setX(disp.getX() + 130 + temp + 10);
    DisplayManager::renderText(to_string(score), disp);
    disp.setX(disp.getX()-temp - 10);

    temp = offset(highScore);
    disp.setX(disp.getX() + 130 + temp);
    DisplayManager::renderText(to_string(highScore), disp);
    disp.setX(disp.getX()-temp);

    temp = offset(missileCountdown);
    disp.setX(disp.getX() + 130 + temp);
    DisplayManager::renderText(to_string(missileCountdown), disp);
    disp.setX(disp.getX()-temp);

    temp = offset(clearScreenCountdown);
    disp.setX(disp.getX() + 145 + temp);
    DisplayManager::renderText(to_string(clearScreenCountdown), disp);
    disp.setX(disp.getX()-temp);

}
    

void Camera::updateCameraPosition(Point shipInitialPoint, Point shipFinalPoint){
    //update the position of the camera with the movement of the ship
    Point renderFinalPoint = DisplayManager::getRenderPointFor(shipFinalPoint, myPoint);
    //if the ship is going way outside the camera then move the camera otherwise do not move the camera
    if (renderFinalPoint.getX() < (DisplayManager::SCREEN_WIDTH / 5) || renderFinalPoint.getX() > DisplayManager::SCREEN_WIDTH - (DisplayManager::SCREEN_WIDTH / 5)){
        myPoint.setX((shipFinalPoint.getX() - shipInitialPoint.getX()) + myPoint.getX());
    } 

}

void Camera::updateMap(SpaceShip* spaceShip, Enemy** enemyList, int enemyListSize, Human* humanList, int humanListSize){
    mapView->render(spaceShip, enemyList, enemyListSize, humanList, humanListSize, myPoint);
}

//new methods by tk
void Camera::setHighScore(int value) {
    highScore = value;
}

int Camera::getHighScore() {
    return highScore;
}
