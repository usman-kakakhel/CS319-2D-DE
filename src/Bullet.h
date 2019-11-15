#ifndef __BULLET_H
#define __BULLET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include  "TargetedWeapon.h"
//#include "Enemy.h"
#include <math.h>

#define PI 3.14159265

class Bullet : public TargetedWeapon{
	public:
		Bullet(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~Bullet();


		//update position method
		void updatePosition() override;
	protected:
		int animation = 0;
};


#endif
