/*
Enemy Class
This class implements all the different types of Enemy. Enemy types inherit from this class
*/
#include "Enemy.h"

// Constructor for any of the enemies created
Enemy::Enemy(Point newPos, int newSpeed, int newOrientation){
    myPoint.setX(newPos.getX());
    myPoint.setY(newPos.getY());
    speed = newSpeed;
    orientation = newOrientation;
    bounty = 5;
}

//  Destructor
Enemy::~Enemy(){
	if (fireBehavior != NULL)
		delete fireBehavior;
}

// Set Position of the enemy
void Enemy::setPosition(Point myPoint){
    Enemy::myPoint = myPoint;
}

// Getting the orientation of the enemy
int Enemy::getOrientation(){
    return orientation;
}

// Set the firing behaviour as the instance coming from FiringBehavior class
void Enemy::setFireBehavior(FiringBehavior* fireBehavior) {
    Enemy::fireBehavior = fireBehavior;
}

Point Enemy::getPosition() const{
    return myPoint;
}
// Set and Get health status of the enemy
void Enemy::setHealthStatus(int health) {
	this->health = health;
}
int Enemy::getHealthStatus() {
	return this->health;
}

int Enemy::getBounty() {
	return this->bounty;
}
// Set as the enemy that is going to be removed from the game
void Enemy::setToBeDestroyed(bool toBeDestroyed) {
	this->toBeDestroyed = toBeDestroyed;
}
bool Enemy::getToBeDestroyed() {
	return this->toBeDestroyed;
}

// Set the mutated enemy so it can be changed from one enemy type to another
void Enemy::setMutated(bool mutated) {
	this->mutated = mutated;
}
bool Enemy::getMutated() {
	return this->mutated;
}

// methds to be overridden in the subtypes
void Enemy::updatePosition(Point spaceShipPos, Human* humanList, int size){
   
}

// FireWeapon  class for any of the enemies, to be overriden later by subclasses
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

// Render method which is overriden by subclasses
void Enemy::render(Point cameraPoint){
        
}

int Enemy::getWidth() {
	return 0;
}

int Enemy::getHeight() {
	return 0;
}
