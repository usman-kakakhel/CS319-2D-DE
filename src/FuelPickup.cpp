#include "FuelPickup.h"

FuelPickup* FuelPickup::instance = NULL;

//Singleton design pattern
FuelPickup* FuelPickup::getInstance(Point newPos, int newAmount){
    if (instance == NULL)
    {
        instance = new FuelPickup(newPos, newAmount);
    }
    return instance;
}

//Destructor and constructor
FuelPickup::FuelPickup(Point newPos, int newAmount) : Pickup(newPos, newAmount){
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(sprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}
FuelPickup::~FuelPickup() {
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}

int FuelPickup::getWidth() {
        return mCTexture->mWidth * 2;
}

int FuelPickup::getHeight() {
        return mCTexture->mHeight * 2;
}


void FuelPickup::render(Point cameraPoint) {
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth * 2, mCTexture->mHeight * 2, this->position, cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE); //need to check this @Usman
}

void FuelPickup::deleteInstance(){
    delete instance;
    instance = NULL;
}
