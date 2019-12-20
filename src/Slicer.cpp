#include "Slicer.h"

Slicer::Slicer(Point newPos, int newSpeed, int newOrientation): Enemy(newPos, newSpeed, newOrientation){
    health = 50;
	FiringBehavior* firingBehavior = new FireRedBolt();
	Enemy::setFireBehavior(firingBehavior);

    if(orientation > 180)
        multiplier = -1;
    else
        multiplier = 1;
    

    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(slicerSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

Slicer::~Slicer(){
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}


//enemy goes toward the ship
void Slicer::updatePosition(Point spaceShipPos, Human* humanList, int size){

    //simpler  movement method
    //myPoint.setX(myPoint.getX() + (multiplier) * ( rand() % speed +0.5) );
    
    //can have another movement method
    myPoint.setX(myPoint.getX() + (speed * (multiplier) * (cos(orientation * PI /180) +0.5)));
    if (myPoint.getX() <= 20 || myPoint.getX() > DisplayManager::GAME_WIDTH - 128) {
        //orientation = abs(180 - orientation);
        multiplier = multiplier * -1;   
    }

    
}

void Slicer::fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos){
	Enemy::fireWeapon(weaponList, size, spaceShipPos);
}

void Slicer::render( Point cameraPoint){
    if (animation < 15)
            animation++;
    else
            animation = 0;

    SDL_Rect clip = { (128 * animation), 0, 128, 128 };
    if(multiplier > 0)
        DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->myPoint, cameraPoint, &clip, 90, NULL, SDL_FLIP_NONE);
    else
        DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->myPoint, cameraPoint, &clip, 270, NULL, SDL_FLIP_NONE);

    
}

int Slicer::getWidth() {
	return 128;
}

int Slicer::getHeight() {
	return 128;
}
