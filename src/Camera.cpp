#include "Camera.h"

Camera::Camera(){

}

Camera::~Camera(){

}

Point Camera::getPoint(){
    return myPoint;
}

void Camera::setPoint(Point myPoint){
    Camera::myPoint = myPoint;
}


Point Camera::getRenderPointFor(Point thePoint){
    thePoint.setX(thePoint.getX() - myPoint.getX());
    return thePoint;
}

void Camera::render(SDL_Renderer* gRenderer){
    // Point backGroundRenderPos = getRenderPointFor(backgroundPos);
    // DisplayManager::render(gRenderer, "../resources/background.jpg", backGroundRenderPos.getX(), backGroundRenderPos.getY());
    //technically rendering the backgroud in the camera so the background does not change even though we are moving constantly
    DisplayManager::render(gRenderer, "../resources/background.jpg", 0, 0);
}

void Camera::updateCameraPosition(Point shipInitialPoint, Point shipFinalPoint){
    //update the position of the camera with the movement of the ship
    Point renderFinalPoint = getRenderPointFor(shipFinalPoint);
    //if the ship is going way outside the camera then move the camera otherwise do not move the camera
    if (renderFinalPoint.getX() < 400 || renderFinalPoint.getX() > 1520)
        myPoint.setX((shipFinalPoint.getX() - shipInitialPoint.getX()) + myPoint.getX());
}