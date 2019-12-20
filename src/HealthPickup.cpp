#include "HealthPickup.h"

HealthPickup* HealthPickup::instance = NULL;

//Singleton design pattern
HealthPickup* HealthPickup::getInstance(Point newPos, int newAmount){
    if (instance == NULL)
    {
        instance = new HealthPickup(newPos, newAmount);
    }
    return instance;
}

//Destructor and constructor
HealthPickup::HealthPickup(Point newPos, int newAmount) : Pickup(newPos, newAmount){
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(sprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}
void HealthPickup::deleteInstance(){
    delete instance;
    instance = NULL;
}
HealthPickup::~HealthPickup() {
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}

int HealthPickup::getWidth() {
	return mCTexture->mWidth * 2;
}

int HealthPickup::getHeight() {
	return mCTexture->mHeight * 2;
}

void HealthPickup::render(Point cameraPoint) {
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth * 2, mCTexture->mHeight * 2, this->position, cameraPoint, NULL, 0, NULL, SDL_FLIP_NONE); //need to check this @Usman
}
