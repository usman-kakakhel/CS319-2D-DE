#include "Asteroid.h"

Asteroid::Asteroid(Point newPos, int newSpeed, int newDamage, int newOrientation):TargetedWeapon(newPos, newSpeed, newDamage,newOrientation){

	mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(asteroidSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

Asteroid::~Asteroid(){
	if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}

int Asteroid::getWidth() {
	return 64;
}

int Asteroid::getHeight() {
	return 64;
}

//update position  method
void Asteroid::updatePosition(){
	Point p(cos((orientation - 90)*(PI/180))*speed + this->getPosition().getX(), sin((orientation - 90)*(PI/180))*speed + this->getPosition().getY());
	this->setPosition(p);
}

void Asteroid::render( Point cameraPoint) {
	 if (asteroidAnimation < 15)
        asteroidAnimation++;
    else
        asteroidAnimation = 0;

	SDL_Rect clip = { (64 * asteroidAnimation), 0, 64, 64 };
	DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->getPosition(), cameraPoint, &clip, orientation);

}
