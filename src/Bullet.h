/*
Bullet Class Header
This class implements the bullet of the spaceship. Bullet has subclasses which different entities in the game fires these different bullets
*/
#ifndef __BULLET_H
#define __BULLET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "TargetedWeapon.h"
#include <math.h>

#define PI 3.14159265

// Bullet class inheriting TargetedWeapon
class Bullet : public TargetedWeapon{
public:
	Bullet(Point newPos, int newSpeed, int newDamage, int newOrientation);
	~Bullet() override;

	//update position method
	void updatePosition() override;
protected:
	int animation = 0;
};


#endif
