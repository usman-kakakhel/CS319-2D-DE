
#ifndef __REDBOLT_H
#define __REDBOLT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h"

class RedBolt : public Bullet{
	public:
		RedBolt(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~RedBolt();
	       void render(SDL_Renderer* gRenderer, Point CameraPoint) override;
        private:

};

#endif

