
#ifndef __BLUEBOLT_H
#define __BLUEBOLT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h"

class BlueBolt : public Bullet{
	public:
		BlueBolt(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~BlueBolt() override;
		int getWidth() override;
		int getHeight() override;
		void render( Point CameraPoint) override;
		
        private:
			//textures and image addresses
			DisplayManager::CustomTexture* mCTexture = NULL;
			string blueSprite = "../resources/blueBolt.png";
                

};

#endif

