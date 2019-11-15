
#ifndef __BLUEBOLT_H
#define __BLUEBOLT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h"

class BlueBolt : public Bullet{
	public:
		BlueBolt(Point newPos, int newSpeed, int newDamage, int newOrientation);
		~BlueBolt();
		void render(SDL_Renderer* gRenderer, Point CameraPoint) override;
        private:
                

};

#endif

