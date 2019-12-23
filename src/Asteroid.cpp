/*
Asteroid Class
This class implements the asteroid feature of the game, which is spawned randomly and hits the spaceship resulting in a health loss for the spaceship.
*/
#include "Asteroid.h"

// Constructor for asteroid
Asteroid::Asteroid(Point newPos, int newSpeed, int newDamage, int newOrientation):TargetedWeapon(newPos, newSpeed, newDamage,newOrientation){

	mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(asteroidSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}
// Destructor for asteroid
Asteroid::~Asteroid(){
	if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}

// Width of the asteroid
int Asteroid::getWidth() {
	return 64;
}

// Height of the asteroid
int Asteroid::getHeight() {
	return 64;
}

//update position method
void Asteroid::updatePosition(){
	Point p(cos((orientation - 90)*(PI/180))*speed + this->getPosition().getX(), sin((orientation - 90)*(PI/180))*speed + this->getPosition().getY());
	this->setPosition(p);
}

// Render the asteroid in display with the given cameraPoint
void Asteroid::render( Point cameraPoint) {
	if (asteroidAnimation < 15)
        asteroidAnimation++;
    else
        asteroidAnimation = 0;

	SDL_Rect clip = { (64 * asteroidAnimation), 0, 64, 64 };
	DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->getPosition(), cameraPoint, &clip, 				orientation);
}
