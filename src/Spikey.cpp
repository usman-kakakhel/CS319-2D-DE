#include "Spikey.h"

Spikey::Spikey(Point newPos, int newSpeed, int newOrientation): Enemy(newPos, newSpeed, newOrientation){
    health = 30;
    
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(spikeySprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

Spikey::~Spikey(){
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}


//enemy goes toward the ship
void Spikey::updatePosition(Point spaceShipPos, Human* humanList, int size){
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
void Spikey::render( Point cameraPoint){
    if (animation < 15)
            animation++;
    else
            animation = 0;

    SDL_Rect clip = { (128 * animation), 0, 128, 128 };

    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->myPoint, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
}

int Spikey::getWidth() {
	return 128;
}

int Spikey::getHeight() {
	return 128;
}

void Spikey::fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos){

}
