#ifndef __ASTEROID_H
#define __ASTEROID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "TargetedWeapon.h"

class Asteroid : public TargetedWeapon{
	public:
		Asteroid(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~Asteroid();

		void updatePosition() override;
		void render(SDL_Renderer* gRenderer, Point CameraPoint) override;
	private:
		string asteroidSprite = "../resources/asteroid.png";
		int asteroidAnimation = 0;
};


#endif
