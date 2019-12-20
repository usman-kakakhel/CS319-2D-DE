#include "Pickup.h"

Pickup::Pickup(Point newPos, int newAmount){
    position.setX(newPos.getX());
    position.setY(newPos.getY());
    amount = newAmount;
}


Pickup::~Pickup(){}

void Pickup::setAmount(int myAmount) {
    amount = myAmount;
}

void Pickup::setPosition(Point thePoint) {
    position.setX(thePoint.getX());
    position.setY(thePoint.getY());
}

void Pickup::setToBeDestroyed(bool toBeDestroyed) {
	this->toBeDestroyed = toBeDestroyed;
}

int Pickup::getAmount() {
    return amount;
}

bool Pickup::getToBeDestroyed() {
	return this->toBeDestroyed;
}

Point Pickup::getPosition() {
    return position;
}

int Pickup::getWidth() {
	return 0;
}

int Pickup::getHeight() {
	return 0;
}

void Pickup::render(Point cameraPoint){

}
