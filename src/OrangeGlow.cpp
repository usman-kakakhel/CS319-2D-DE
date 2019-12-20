#include "OrangeGlow.h"

//constructor
OrangeGlow::OrangeGlow(Point newPos, int newSpeed, int newDamage, int newOrientation): Bullet(newPos, newSpeed, newDamage, newOrientation){
        mCTexture = new DisplayManager::CustomTexture();
        DisplayManager::loadFromFile(orangeGlowSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

//destructor
OrangeGlow::~OrangeGlow(){
        if (mCTexture != NULL){
                delete mCTexture->mTexture;
                delete mCTexture;
        }
}

int OrangeGlow::getWidth() {
	return 32;
}

int OrangeGlow::getHeight() {
	return 32;
}

void OrangeGlow::render(Point cameraPoint) {
       if (animation < 16)
                animation++;
        else
                animation = 0;
        
        SDL_Rect clip = { (32 * (animation % 4)), (32 * (animation / 4)), 32, 32 };

        DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->position, cameraPoint, &clip, orientation, NULL, SDL_FLIP_NONE);
}

