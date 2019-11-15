
#ifndef __ORANGEGLOW_H
#define __ORANGEGLOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h"

class OrangeGlow : public Bullet{
	public:
		OrangeGlow(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~OrangeGlow();
                void render(SDL_Renderer* gRenderer, Point CameraPoint) override;
        private:
                string orangeGlowSprite;

};

#endif

