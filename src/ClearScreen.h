
#ifndef __CLEARSCREEN_H
#define __CLEARSCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "MassDestructionWeapon.h"

class ClearScreen : public MassDestructionWeapon{
	public:
		ClearScreen(int damageValue, int radiusValue);
		~ClearScreen();
};

#endif

