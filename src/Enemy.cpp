#include "Enemy.h"
// struct fire{
//     TargetedWeapon*** weaponList;
//     int* size;
//     Point* spaceShipPos;
//     Enemy* enemy;
// };

// typedef struct fire fire;

//Enemy::Enemy(Point newPos, int newSpeed, int newOrientation, TargetedWeapon** &weaponList, int &size, Point const &spaceShipPos){
    Enemy::Enemy(Point newPos, int newSpeed, int newOrientation){
    myPoint.setX(newPos.getX());
    myPoint.setY(newPos.getY());
    speed = newSpeed;
    orientation = newOrientation;
    // setTimer(&weaponList, &size, &spaceShipPos);
}

// Uint32 firingTimer(Uint32 interval, void* param){
//     TargetedWeapon*** weaponList = ((fire*)param)->weaponList;
//     int* size = ((fire*)param)->size;
//     Point* spaceShipPos = ((fire*)param)->spaceShipPos;
//     Enemy* enemy = ((fire*)param)->enemy;
//     enemy->fireWeapon(*weaponList, *size, *spaceShipPos);
// }
// fire* myFire;
// void Enemy::setTimer(TargetedWeapon*** weaponList, int* size, Point* spaceShipPos){
//     myFire = (fire*)malloc(sizeof(fire));
//     myFire->size = size;
//     myFire->spaceShipPos = spaceShipPos;
//     myFire->weaponList = weaponList;
//     myFire->enemy = this;
//     timerID = SDL_AddTimer( 3 * 1000, firingTimer, myFire);
// }

void Enemy::setPoint(Point myPoint){
    Enemy::myPoint = myPoint;
}

Point Enemy::getPoint() const{
    return myPoint;
}
//enemy goes toward the ship
void Enemy::updatePosition(Point spaceShipPos){
    // int myX = myPoint.getX();
    // int myY = myPoint.getY();
    // int shipX = spaceShipPos.getX(); 
    // int shipY = spaceShipPos.getY();
    // //go toward ship X    
    // if( shipX - followAccuracy > myX)
    //     myPoint.setX(myX+speed);
    // else if(shipX + followAccuracy < myX)
    //     myPoint.setX(myX-speed);
    // //go toward ship Y
    // if(shipY - followAccuracy > myY)
    //     myPoint.setY(myY+speed);
    // else if(shipY + followAccuracy < myY)
    //     myPoint.setY(myY-speed);
    
    myPoint.setX(myPoint.getX() + (speed * cos(orientation * PI /180)));
    myPoint.setY(myPoint.getY() + (speed * sin(orientation * PI /180)));

    if (myPoint.getX() < 0 || myPoint.getX() > GAME_WIDTH) {
        orientation = abs(180 - orientation);   
    }
    else if (myPoint.getY() < 0 || myPoint.getY() > SCREEN_HEIGHT) {
        orientation = abs(360 - orientation); 
    }
}



// void Enemy::fireWeapon(TargetedWeapon** &weaponList, int &size, Point &spaceShipPos){
    
//     int newOrientation = atan2(spaceShipPos.getY() - myPoint.getY(), spaceShipPos.getX() - myPoint.getY()) * 180/PI;
//     Point newPos = myPoint;
    
//     //make a new list of weapons
//     size++;
//     TargetedWeapon** newList = new TargetedWeapon*[size];
    
//     //copy existing list to new one
//     for (int i = 0; i < size - 1; i++){
//         newList[i] = weaponList[i];
//     }
//     //new bullet
//     newList[(size - 1)] = new RedBolt(newPos, 40, 50, newOrientation);
//     //delete existing list
//     delete [] weaponList;

//     weaponList = newList;
// }


void Enemy::render(SDL_Renderer* gRenderer, Point cameraPoint){
        
}


Enemy::~Enemy(){
    // SDL_RemoveTimer( timerID );
    // delete myFire;
}
