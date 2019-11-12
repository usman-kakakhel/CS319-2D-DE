#include "SpaceShip.h"


SpaceShip::SpaceShip(){
    myPoint.setX(400);
    myPoint.setY(500);
    orientation = RIGHT;
    prevOrientation = RIGHT;
}

SpaceShip::~SpaceShip(){
}

Point SpaceShip::getPoint(){
    return myPoint;
}


Orientation SpaceShip::getOrientation(){
    return orientation;
}

void SpaceShip::setPoint(Point myPoint){
    SpaceShip::myPoint = myPoint;
}


void SpaceShip::updatePosition(){
    //update the position of the spaceship in the direction it is according to its speed
    if (orientation == RIGHT){
        myPoint.setX(myPoint.getX() + speed);
    }
    else if (orientation == UP && myPoint.getY() > 130){
        myPoint.setY(myPoint.getY() - speed);
    }
    else if (orientation == DOWN && myPoint.getY() < 850){
        myPoint.setY(myPoint.getY() + speed);
    }
    else if (orientation == LEFT){
        myPoint.setX(myPoint.getX() - speed);
    }
}

void SpaceShip::setOrientation(Orientation orientation){
    //prevOrientation shows the direction left or right the ship is in and orientation shows the up and down tilt
    if (orientation == RIGHT || orientation == LEFT)
        prevOrientation = orientation;
    this->orientation = orientation;
}


void SpaceShip::render(SDL_Renderer* gRenderer, Point cameraPoint){

    //render the image according to the direction the ship is in
    if (prevOrientation == RIGHT){
        DisplayManager::render(gRenderer, spriteList[(int)orientation], myPoint, cameraPoint, NULL, 90, NULL, SDL_FLIP_NONE);
    }
    else if (prevOrientation == LEFT){
        if (orientation == LEFT)
            DisplayManager::render(gRenderer, spriteList[RIGHT], myPoint, cameraPoint, NULL, 270, NULL, SDL_FLIP_HORIZONTAL);
        else
            DisplayManager::render(gRenderer, spriteList[(int)orientation], myPoint, cameraPoint, NULL, 270, NULL, SDL_FLIP_HORIZONTAL);
    }
    //when the render is done, set the orientation to directional rather than tilt
    orientation = prevOrientation;
}