#include "BlueBolt.h"

//constructor
BlueBolt::BlueBolt(Point newPos, int newSpeed, int newDamage, int newOrientation): Bullet(newPos, newSpeed, newDamage, newOrientation){
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(blueSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

//destructor
BlueBolt::~BlueBolt(){
        if (mCTexture != NULL){
                delete mCTexture->mTexture;
                delete mCTexture;
        }
}

int BlueBolt::getWidth() {
	return 32;
}

int BlueBolt::getHeight() {
	return 32;
}

void BlueBolt::render(Point cameraPoint) {
        if (animation < 15)
                animation++;
        else
                animation = 0;

        SDL_Rect clip = { (32 * animation), 0, 32, 64 };

        DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->position, cameraPoint, &clip, orientation, NULL, SDL_FLIP_NONE);
}


