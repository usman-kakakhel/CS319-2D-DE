#include "Enemy.h"

Enemy::Enemy(Point newPos, int newSpeed, int newOrientation){
    myPoint.setX(newPos.getX());
    myPoint.setY(newPos.getY());
    speed = newSpeed;
    orientation = newOrientation;
    bounty = 5;
}

void Enemy::setPosition(Point myPoint){
    Enemy::myPoint = myPoint;
}

int Enemy::getOrientation(){
    return orientation;
}

void Enemy::setFireBehavior(FiringBehavior* fireBehavior) {
    Enemy::fireBehavior = fireBehavior;
}

Point Enemy::getPosition() const{
    return myPoint;
}

void Enemy::setHealthStatus(int health) {
	this->health = health;
}

int Enemy::getHealthStatus() {
	return this->health;
}

int Enemy::getBounty() {
	return this->bounty;
}

void Enemy::setToBeDestroyed(bool toBeDestroyed) {
	this->toBeDestroyed = toBeDestroyed;
}

bool Enemy::getToBeDestroyed() {
	return this->toBeDestroyed;
}

void Enemy::setMutated(bool mutated) {
	this->mutated = mutated;
}

bool Enemy::getMutated() {
	return this->mutated;
}

//methds to be overridden in the subtypes
void Enemy::updatePosition(Point spaceShipPos, Human* humanList, int size){
    
}


void Enemy::fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos){
    if (shootInterval >= 125){
        int newOrientation = atan2(spaceShipPos.getY() - myPoint.getY(), spaceShipPos.getX() - myPoint.getX()) * 180/PI;
        Point newPos = myPoint;
        newPos.setX(newPos.getX() + 64);
        fireBehavior->fire(weaponList, size, spaceShipPos, newPos, newOrientation + 90);
        shootInterval = 0;
    }
    else{
        shootInterval++;
    }
}


void Enemy::render(Point cameraPoint){
        
}

int Enemy::getWidth() {
	return 0;
}

int Enemy::getHeight() {
	return 0;
}

Enemy::~Enemy(){
    if (fireBehavior != NULL)
	    delete fireBehavior;
}
