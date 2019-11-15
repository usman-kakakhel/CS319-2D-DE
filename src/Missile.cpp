#include "Missile.h"

Missile::Missile(Point newPos, int newSpeed, int newDamage, int newOrientation):TargetedWeapon(newPos, newSpeed, newDamage){
        this->orientation = newOrientation;
}

Missile::~Missile(){

}

int Missile::getOrientation() {
        return this->orientation;
}

void Missile::setOrientation(int newOrientation) {
        this->orientation = newOrientation;
}

void Missile::updatePosition() {
        Point p(this->getPosition().getX(), this->getPosition().getY() + speed);
	this->setPosition(p);
}

void Missile::render(SDL_Renderer* gRenderer, Point cameraPoint) {
        DisplayManager::render(gRenderer, "../resources/missile.png", this->position, cameraPoint, NULL, this->orientation, NULL, SDL_FLIP_NONE);
}

