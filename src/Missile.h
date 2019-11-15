
#ifndef __MISSILE_H
#define __MISSILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include  "TargetedWeapon.h"
//#include "Enemy.h"
#include <math.h>

#define PI 3.14159265

class Missile : public TargetedWeapon{
        public:
                Missile(Point newPos, int newSpeed, int newDamage, int newOrientation);
                ~Missile();
                int getOrientation();
                void setOrientation(int newOrientation);

                void render(SDL_Renderer* gRenderer, Point CameraPoint);
                //update position method
                void updatePosition();

        private:
                int orientation;
};



#endif