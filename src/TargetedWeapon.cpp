#include "TargetedWeapon.h"

//constructor
TargetedWeapon::TargetedWeapon(Point newPos, int newSpeed, int newDamage, int newOrientation){
	this->position = newPos;
	this->speed = newSpeed;
	this->damage = newDamage;
	this->orientation = newOrientation;
}

//destructor
TargetedWeapon::~TargetedWeapon(){

}

//setter methods
void TargetedWeapon::setPosition(Point newPos){
	this->position = newPos;
}

void TargetedWeapon::setDamage(int newDamage){
	this->damage = newDamage;
}

void TargetedWeapon::setSpeed(int newSpeed){
	this->speed = newSpeed;
}

//getter methods
Point TargetedWeapon::getPosition() const{
	return this->position;
}

int TargetedWeapon::getDamage() const{
	return this->damage;
}

int TargetedWeapon::getSpeed() const{
	return this->speed;
}


void TargetedWeapon::operator= (TargetedWeapon const &weapon){
	this->position = weapon.position;
	this->damage = weapon.damage;
	this->speed = weapon.speed;
	this->orientation = weapon.orientation;
}

int TargetedWeapon::getOrientation() const{
	return orientation;
}
void TargetedWeapon::setOrientation(int newOrientation){
	this->orientation = newOrientation;
}

void TargetedWeapon::render(SDL_Renderer* gRenderer, Point cameraPoint){}
void TargetedWeapon::updatePosition(){}