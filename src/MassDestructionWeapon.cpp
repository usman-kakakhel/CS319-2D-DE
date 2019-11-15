#include "MassDestructionWeapon.h"

//constructor
MassDestructionWeapon::MassDestructionWeapon(int damageValue, int radiusValue){
	damage = damageValue;
	blastRadius = radiusValue;
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

int MassDestructionWeapon::getDamage(){
	return this->damage;
}

int MassDestructionWeapon::getBlastRadius(){
	return this->blastRadius;
}

// void MassDestructionWeapon::destroy(Enemy* enemyList, Point blastCenter, int &listLength){
// 	Enemy closest;
// 	for(int a = 0; a < listLength; a++){
// 		int xDiff;
// 		int yDiff;
// 		int temp;
// 		//calculating distance between enemy and center
// 		xDiff = enemyList[a].getPosition().getX() - blastCenter.getX();
// 		xDiff = xDiff * xDiff;
// 		yDiff = enemyList[a].getPosition().getY() - blastCeter.getY();
// 		yDiff = yDiff * yDiff;
// 		temp = xDiff + yDiff;
// 		temp = (int)round(sqrt((double)temp));
// 		//comapring distance and then deleting enemy if in range.
// 		if (temp <= this->blastRadius){
// 			//need to delete this enemy
// 			Enemy *newList;
// 			for (int x = 0; x < a; x++){
// 				newList[x] = enemyList[x];
// 			}
// 			for(int x = a + 1; x < listLength; x++){
// 				newList[x - 1] = enemyList[x];
// 			}
// 			listLength--;
// 			//delete the enemyList element
// 			//copying the newList into enemyList with update size
// 			enemyList = newList;
// 		}
// 	}
// }
