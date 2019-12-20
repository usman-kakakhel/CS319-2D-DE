#ifndef __ASTEROID_H
#define __ASTEROID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "TargetedWeapon.h"

#define PI 3.14159265

class Asteroid : public TargetedWeapon{
	public:
		Asteroid(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~Asteroid() override;
		int getWidth();
		int getHeight();

		void updatePosition() override;
		void render(Point CameraPoint) override;
	private:
		int asteroidAnimation = 0;

		//textures and image addresses
		DisplayManager::CustomTexture* mCTexture = NULL;
		string asteroidSprite = "../resources/asteroid.png";
		
};


#endif
