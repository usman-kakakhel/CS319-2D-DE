#ifndef __MASSDESTRUCTIONWEAPON_H
#define __MASSDESTRUCTIONWEAPON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Weapon.h"
#include "Point.h"
#include "Enemy.h"
#include <math.h>

class MassDestructionWeapon : public Weapon{
    public:
        MassDestructionWeapon(Point blastCenter, int damageValue, int radiusValue);
        ~MassDestructionWeapon();
	
	virtual void destroy(Enemy** &enemyList, int &listLength, Point cameraPoint);
	//setter methods
	void setDamage(int damageValue);
	void setBlastRadius(int radiusValue);
	void setBlastCenter(Point blastCenter);
	//getter methods
	int getDamage();
	int getBlastRadius();
	Point getBlastCenter();


    protected:
        int damage;
		int blastRadius;
		Point blastCenter;
};

#endif
