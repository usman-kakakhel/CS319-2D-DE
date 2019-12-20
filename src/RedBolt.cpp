#include "RedBolt.h"

//constructor
RedBolt::RedBolt(Point newPos, int newSpeed, int newDamage, int newOrientation): Bullet(newPos, newSpeed, newDamage, newOrientation){
        mCTexture = new DisplayManager::CustomTexture();
        DisplayManager::loadFromFile(redSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

//destructor
RedBolt::~RedBolt(){
        if (mCTexture != NULL){
                delete mCTexture->mTexture;
                delete mCTexture;
        }
}

int RedBolt::getWidth() {
	return 32;
}

int RedBolt::getHeight() {
	return 64;
}

void RedBolt::render( Point cameraPoint) {
       if (animation < 15)
                animation++;
        else
                animation = 0;
        
        SDL_Rect clip = { (32 * animation), 0, 32, 64 };

        DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->position, cameraPoint, &clip, orientation, NULL, SDL_FLIP_NONE);
}

