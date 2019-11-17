#include "Enemy.h"
Enemy::Enemy(){
    myPoint.setX(SCREEN_WIDTH / 4);
    myPoint.setY(SCREEN_HEIGHT / 3);
}
void Enemy::setPoint(Point myPoint){
    Enemy::myPoint = myPoint;
}
//enemy goes toward the ship
void Enemy::updatePosition(Point spaceShipPos){
    int myX = myPoint.getX();
    int myY = myPoint.getY();
    int shipX = spaceShipPos.getX(); 
    int shipY = spaceShipPos.getY();
//go toward ship X    
    if( shipX - followAccuracy > myX)
        myPoint.setX(myX+speed);
    else if(shipX + followAccuracy < myX)
        myPoint.setX(myX-speed);
//go toward ship Y
    if(shipY - followAccuracy > myY)
        myPoint.setY(myY+speed);
    else if(shipY + followAccuracy < myY)
        myPoint.setY(myY-speed);
}
void Enemy::render(SDL_Renderer* gRenderer, Point cameraPoint){
        DisplayManager::render(gRenderer, spritePath, myPoint, cameraPoint, NULL, 90, NULL, SDL_FLIP_NONE);
}
Enemy::~Enemy(){
}

