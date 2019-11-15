#include "Asteroid.h"

Asteroid::Asteroid(Point newPos, int newSpeed, int newDamage, int newOrientation):TargetedWeapon(newPos, newSpeed, newDamage,newOrientation){
	
}

Asteroid::~Asteroid(){

}

//update position  method
void Asteroid::updatePosition(){
	Point p(this->getPosition().getX(), this->getPosition().getY() + speed);
	this->setPosition(p);
}

void Asteroid::render(SDL_Renderer* gRenderer, Point cameraPoint) {
	 if (asteroidAnimation < 16)
        asteroidAnimation++;
    else
        asteroidAnimation = 0;

	SDL_Rect clip = { (64 * asteroidAnimation), 0, 64, 64 };
	DisplayManager::render(gRenderer, asteroidSprite, this->getPosition(), cameraPoint, &clip, orientation);

}
