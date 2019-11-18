#include "Camera.h"

Camera::Camera(){
    numOfHills = (GAME_WIDTH / 808) + 1;
    backgroundPosStart = new Point[numOfHills];
    for (int i = 0; i < numOfHills; i++){
        Point a((i * 808), SCREEN_HEIGHT  - 130);
        backgroundPosStart[i] = a;
    }
}

Camera::~Camera(){

}

Point Camera::getPoint(){
    return myPoint;
}

void Camera::setPoint(Point myPoint){
    Camera::myPoint = myPoint;
}



void Camera::render(SDL_Renderer* gRenderer, int health, int fuel, int coin, int score, int highScore, int missileCountdown, int clearScreenCountdown){
    // Point backGroundRenderPos = getRenderPointFor(backgroundPos);
    // DisplayManager::render(gRenderer, "../resources/background.jpg", backGroundRenderPos.getX(), backGroundRenderPos.getY());
    //technically rendering the backgroud in the camera so the background does not change even though we are moving constantly
    DisplayManager::render(gRenderer, "../resources/background.jpg", 0, 0);
    
    //display the hills
    Point hillPoint(0, backgroundPosStart[0].getY());
    int  x = (myPoint.getX() / 808) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(gRenderer, "../resources/ground.png", hillPoint, myPoint);
    x = ((myPoint.getX() / 808) + 1) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(gRenderer, "../resources/ground.png", hillPoint, myPoint);
    x = ((myPoint.getX() / 808) + 2) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(gRenderer, "../resources/ground.png", hillPoint, myPoint);
    x = ((myPoint.getX() / 808) + 3) % numOfHills;
    hillPoint.setX(backgroundPosStart[x].getX());
    DisplayManager::render(gRenderer, "../resources/ground.png", hillPoint, myPoint);

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
        DisplayManager::render(gRenderer, spriteList[i], spriteDisp, 0);
    }
    //rendering texts for stats
    disp.setY(50);
    disp.setX(145);
    renderText(gRenderer, to_string(health), disp);
    disp.setX(disp.getX() + 130);
    renderText(gRenderer, to_string(fuel), disp);
    disp.setX(disp.getX() + 130);
    renderText(gRenderer, to_string(coin), disp);
    disp.setX(disp.getX() + 130);
    renderText(gRenderer, to_string(score), disp);
    disp.setX(disp.getX() + 130);
    renderText(gRenderer, to_string(highScore), disp);
    disp.setX(disp.getX() + 130);
    renderText(gRenderer, to_string(missileCountdown), disp);
    disp.setX(disp.getX() + 130);
    renderText(gRenderer, to_string(clearScreenCountdown), disp);

}
    

void Camera::updateCameraPosition(Point shipInitialPoint, Point shipFinalPoint){
    //update the position of the camera with the movement of the ship
    Point renderFinalPoint = getRenderPointFor(shipFinalPoint, myPoint);
    //if the ship is going way outside the camera then move the camera otherwise do not move the camera
    if (renderFinalPoint.getX() < (SCREEN_WIDTH / 5) || renderFinalPoint.getX() > SCREEN_WIDTH - (SCREEN_WIDTH / 5)){
        myPoint.setX((shipFinalPoint.getX() - shipInitialPoint.getX()) + myPoint.getX());
    } 

}