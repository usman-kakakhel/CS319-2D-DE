#ifndef __NUCLEARBOMB_H
#define __NUCLEARBOMB_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "MassDestructionWeapon.h"
#include "Enemy.h"

class NuclearBomb : public MassDestructionWeapon{
	public:
		NuclearBomb(Point blastCenter, int damageValue = 100, int radiusValue = 0);
		~NuclearBomb();
		void destroy(Enemy** &enemyList, int &listLength, Point CameraPoint) override;
};

#endif

