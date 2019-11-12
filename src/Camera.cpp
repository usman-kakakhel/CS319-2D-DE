#include "Camera.h"

Camera::Camera(){
    backgroundPosStart.setY(SCREEN_HEIGHT  - 130);
    trick = 0;
}

Camera::~Camera(){

}

Point Camera::getPoint(){
    return myPoint;
}

void Camera::setPoint(Point myPoint){
    Camera::myPoint = myPoint;
}



void Camera::render(SDL_Renderer* gRenderer){
    // Point backGroundRenderPos = getRenderPointFor(backgroundPos);
    // DisplayManager::render(gRenderer, "../resources/background.jpg", backGroundRenderPos.getX(), backGroundRenderPos.getY());
    //technically rendering the backgroud in the camera so the background does not change even though we are moving constantly
    DisplayManager::render(gRenderer, "../resources/background.jpg", 0, 0);
    //display the hills
    if (trick){
        Point dispPoint = backgroundPosStart;
        DisplayManager::render(gRenderer, "../resources/ground.png", dispPoint, myPoint);
        dispPoint.setX(dispPoint.getX() + 800);
        DisplayManager::render(gRenderer, "../resources/ground.png", dispPoint, myPoint);
        dispPoint.setX(dispPoint.getX() + 800);
        DisplayManager::render(gRenderer, "../resources/ground.png", dispPoint, myPoint);
    }
    else {
        Point trickPoint;
        trickPoint.setX(backgroundPosStart.getX() - 100);
        trickPoint.setY(SCREEN_HEIGHT  - 130);
        DisplayManager::render(gRenderer, "../resources/ground.png", trickPoint, myPoint);
        trickPoint.setX(trickPoint.getX() + 800);
        DisplayManager::render(gRenderer, "../resources/ground.png", trickPoint, myPoint);
        trickPoint.setX(trickPoint.getX() + 800);
        DisplayManager::render(gRenderer, "../resources/ground.png", trickPoint, myPoint);
    }
}
    

void Camera::updateCameraPosition(Point shipInitialPoint, Point shipFinalPoint){
    //update the position of the camera with the movement of the ship
    Point renderFinalPoint = getRenderPointFor(shipFinalPoint, myPoint);
    //if the ship is going way outside the camera then move the camera otherwise do not move the camera
    if (renderFinalPoint.getX() < (SCREEN_WIDTH / 5) || renderFinalPoint.getX() > SCREEN_WIDTH - (SCREEN_WIDTH / 5)){
        myPoint.setX((shipFinalPoint.getX() - shipInitialPoint.getX()) + myPoint.getX());
    } 
    backgroundPosStart.setX((shipFinalPoint.getX() - shipInitialPoint.getX()) + myPoint.getX());
    if (trick){trick = 0;}
    else{trick = 1;}
}