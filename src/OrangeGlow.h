
#ifndef __ORANGEGLOW_H
#define __ORANGEGLOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h"

class OrangeGlow : public Bullet{
	public:
		OrangeGlow(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~OrangeGlow() override;
		int getWidth() override;
		int getHeight() override;
                void render(Point CameraPoint) override;
        private:
                //textures and image addresses
		DisplayManager::CustomTexture* mCTexture = NULL;
                string orangeGlowSprite = "../resources/orangeGlow.png";

};

#endif

