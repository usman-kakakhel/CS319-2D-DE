#include "MassDestructionWeapon.h"

//constructor
MassDestructionWeapon::MassDestructionWeapon(Point blastCenter, int damageValue, int radiusValue){
	damage = damageValue;
	blastRadius = radiusValue;
	this->blastCenter = blastCenter;
}

//destructor
MassDestructionWeapon::~MassDestructionWeapon(){
	damage = 0;
	blastRadius = 0;
}

void MassDestructionWeapon::setDamage(int damageValue){
	damage = damageValue;
}

void MassDestructionWeapon::setBlastRadius(int radiusValue){
	blastRadius = radiusValue;
}

void MassDestructionWeapon::setBlastCenter(Point blastCenter) {
	this->blastCenter = blastCenter;
}

int MassDestructionWeapon::getDamage(){
	return this->damage;
}

int MassDestructionWeapon::getBlastRadius(){
	return this->blastRadius;
}

Point MassDestructionWeapon::getBlastCenter() {
	return this->blastCenter;
}

void MassDestructionWeapon::destroy(Enemy** &enemyList, int &listLength, Point cameraPoint) {

}
