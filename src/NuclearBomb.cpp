#include "NuclearBomb.h"

//constructor
NuclearBomb::NuclearBomb(Point blastCenter, int damageValue, int radiusValue): MassDestructionWeapon(blastCenter, damageValue, radiusValue){
        
}

//destructor
NuclearBomb::~NuclearBomb(){
        damage = 0;
        blastRadius = 0;
}

void NuclearBomb::destroy(Enemy** &enemyList, int &listLength, Point cameraPoint){
	for(int i = 0; i < listLength; i++){

		//calculating distance between enemy and center
		bool isInScreen = true;

		if(enemyList[i]->getPosition().getX() < cameraPoint.getX() || enemyList[i]->getPosition().getX() > cameraPoint.getX() + DisplayManager::SCREEN_WIDTH) {
			isInScreen = false;
		}

		//comapring distance and then deleting enemy if in range.
		if (isInScreen){
			enemyList[i]->setToBeDestroyed(true);
		}
	}
}
