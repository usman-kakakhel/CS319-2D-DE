#ifndef __MASSDESTRUCTIONWEAPON_H
#define __MASSDESTRUCTIONWEAPON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Weapon.h"
#include "Point.h"
//#include "Enemy.h"
#include <math.h>

class MassDestructionWeapon : public Weapon{
    public:
        MassDestructionWeapon(int damageValue, int radiusValue);
        ~MassDestructionWeapon();
	
	//void destroy(Enemy* enemyList, Point blastCenter, int listLength);
	//setter methods
	void setDamage(int damageValue);
	void setBlastRadius(int radiusValue);
	//getter methods
	int getDamage();
	int getBlastRadius();

    protected:
        int damage;
		int blastRadius;
};

#endif
