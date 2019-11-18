#include "Saucer.h"

//Saucer::Saucer(Point newPos, int newSpeed, int newOrientation, TargetedWeapon** &weaponList, int &size, Point const &spaceShipPos): Enemy(newPos, newSpeed, newOrientation, weaponList, size, spaceShipPos){
    Saucer::Saucer(Point newPos, int newSpeed, int newOrientation): Enemy(newPos, newSpeed, newOrientation){

}

Saucer::~Saucer(){}


void Saucer::render(SDL_Renderer* gRenderer, Point cameraPoint){
    if (animation < 15)
            animation++;
    else
            animation = 0;

    SDL_Rect clip = { (128 * animation), 0, 128, 128 };

    DisplayManager::render(gRenderer, "../resources/saucer.png", this->myPoint, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
}