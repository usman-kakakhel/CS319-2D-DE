#include "TargetedWeapon.h"

//constructor
TargetedWeapon::TargetedWeapon(Point newPos, int newSpeed, int newDamage){
	this->position = newPos;
	this->speed = newSpeed;
	this->damage = newDamage;
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

void TargetedPosition::setSpeed(int newSpeed){
	this->speed = newSpeed;
}

//getter methods
Point TargetedWeapon::getPosition(){
	return this->position;
}

int TargetedWeapon::getDamage(){
	return this->damage;
}

int TargetedWeapon::getSpeed(){
	return this->speed;
}
