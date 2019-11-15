#include "SpaceShip.h"
#include "iostream"

SpaceShip::SpaceShip(){
    myPoint.setX(SCREEN_WIDTH / 5);
    myPoint.setY(SCREEN_HEIGHT / 2);
    orientation = RIGHT;
    prevOrientation = RIGHT;
}

SpaceShip::~SpaceShip(){
}

Point SpaceShip::getPoint(){
    return myPoint;
}

int SpaceShip::getHealthStatus(){
    return healthStatus;
}
int SpaceShip::getFuelStatus(){
    return fuelStatus;
}
int SpaceShip::getMissileCountdown(){
    return missileCountdown;
}
int SpaceShip::getClearScreenCountdown(){
    return clearScreenCountdown;
}


Orientation SpaceShip::getOrientation(){
    return orientation;
}

void SpaceShip::setPoint(Point myPoint){
    SpaceShip::myPoint = myPoint;
}


void SpaceShip::updatePosition(){
    isMoving = true;
    //update the position of the spaceship in the direction it is according to its speed
    if (orientation == RIGHT){
        if (myPoint.getX() > GAME_WIDTH - (SCREEN_WIDTH / 5)){
            myPoint.setX(SCREEN_WIDTH / 5);
        }
        else{
            myPoint.setX(myPoint.getX() + speed);
        }
    }
    else if (orientation == UP && myPoint.getY() > (SCREEN_HEIGHT / 8)){
        myPoint.setY(myPoint.getY() - speed);
    }
    else if (orientation == DOWN && myPoint.getY() < SCREEN_HEIGHT - (SCREEN_HEIGHT / 4)){
        myPoint.setY(myPoint.getY() + speed);
    }
    else if (orientation == LEFT){
        if (myPoint.getX() < (SCREEN_WIDTH / 5) ){
            myPoint.setX(GAME_WIDTH - (SCREEN_WIDTH / 5));
        }
        else{
            myPoint.setX(myPoint.getX() - speed);
        }
    }
}

void SpaceShip::setOrientation(Orientation orientation){
    //prevOrientation shows the direction left or right the ship is in and orientation shows the up and down tilt
    if (orientation == RIGHT || orientation == LEFT)
        prevOrientation = orientation;
    this->orientation = orientation;
}


void SpaceShip::render(SDL_Renderer* gRenderer, Point cameraPoint){
    if (fireAnimation < 16)
        fireAnimation++;
    else
        fireAnimation = 0;
    
    //render the image according to the direction the ship is in
    if (prevOrientation == RIGHT){
        DisplayManager::render(gRenderer, spriteList[(int)orientation], myPoint, cameraPoint, NULL, 90, NULL, SDL_FLIP_NONE);
        if(isMoving){
            SDL_Rect clip = { (64 * fireAnimation), 0, 64, 128 };
            Point firePoint = myPoint;
            firePoint.setX(firePoint.getX() - 65);
            DisplayManager::render(gRenderer, "../resources/thrust.png", firePoint, cameraPoint, &clip, 90, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
    else if (prevOrientation == LEFT){
        if (orientation == LEFT){
            DisplayManager::render(gRenderer, spriteList[RIGHT], myPoint, cameraPoint, NULL, 270, NULL, SDL_FLIP_HORIZONTAL);
        }
        else{
            DisplayManager::render(gRenderer, spriteList[(int)orientation], myPoint, cameraPoint, NULL, 270, NULL, SDL_FLIP_HORIZONTAL);
        }
        if (isMoving){
            SDL_Rect clip = { (64 * fireAnimation), 0, 64, 128 };
            Point firePoint = myPoint;
            firePoint.setX(firePoint.getX() + 130);
            DisplayManager::render(gRenderer, "../resources/thrust.png", firePoint, cameraPoint, &clip, 270, NULL, SDL_FLIP_HORIZONTAL);  
        } 
    }
    //when the render is done, set the orientation to directional rather than tilt
    orientation = prevOrientation;
    isMoving = false;
}


void SpaceShip::fireBullet(TargetedWeapon** &weaponList, int &size){
    int newOrientation = 0;
    Point newPos = myPoint;
    if (prevOrientation == LEFT){
        newOrientation = 270;
        newPos.setX(newPos.getX() - 0);
        newPos.setY(newPos.getY() + 32);
    }
    else{
        newOrientation = 90;
        newPos.setX(newPos.getX() + 84);
        newPos.setY(newPos.getY() + 32);
    }
    //make a new list of weapons
    size++;
    TargetedWeapon** newList = new TargetedWeapon*[size];
    
    //copy existing list to new one
    for (int i = 0; i < size - 1; i++){
        newList[i] = weaponList[i];
    }
    //new bullet
    newList[(size - 1)] = new BlueBolt(newPos, 40, 50, newOrientation);
    //delete existing list
    delete [] weaponList;

    weaponList = newList;
}