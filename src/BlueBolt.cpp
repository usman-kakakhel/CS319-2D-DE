/*
BlueBolt Class
This class implements the blueBolt bullet of the game. BlueBolt is the bullet which the player's spaceship  can shoot by pressing button 'z'.
*/
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

// Get width of the bluebolt
int BlueBolt::getWidth() {
	return 32;
}

// Get height of the bluebolt
int BlueBolt::getHeight() {
	return 32;
}

// Render the blueBolt bullet in the cameraview
void BlueBolt::render(Point cameraPoint) {
    if (animation < 15)
        animation++;
    else
        animation = 0;
	// Each bullet is rendered as an SDL_Rect, to detect collision later too.
    SDL_Rect clip = { (32 * animation), 0, 32, 64 };
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->position, cameraPoint, &clip, orientation, NULL, 			SDL_FLIP_NONE);
}


