#ifndef __TARGETEDWEAPON_H
#define __TARGETEDWEAPON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Weapon.h"
#include "Point.h"

class TargetedWeapon : public Weapon{
    public:
        TargetedWeapon(Point newPos, int newSpeed, int newDamage);
        ~TargetedWeapon();

	//setter methods
	void setPosition(Point newPos);
	void setSpeed(int newSpeed);
	void setDamage(int newDamage);
	//getter methods
	Point getPosition();
	int getSpeed();
	int getDamage();

    private:
	Point position;
	int speed;
	int damage;
};

#endif
