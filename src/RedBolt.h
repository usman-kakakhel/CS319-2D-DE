
#ifndef __REDBOLT_H
#define __REDBOLT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h"

class RedBolt : public Bullet{
	public:
		RedBolt(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~RedBolt() override;
		int getWidth() override;
		int getHeight() override;
	       void render( Point CameraPoint) override;
        private:
			//textures and image addresses
			DisplayManager::CustomTexture* mCTexture = NULL;
			string redSprite = "../resources/redBolt.png";
};

#endif

