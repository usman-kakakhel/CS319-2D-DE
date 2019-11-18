#ifndef __SAUCER_H
#define __SAUCER_H

#include "Enemy.h"

class Saucer : public Enemy{
    public:
        //Saucer(Point newPos, int newSpeed, int newOrientation, TargetedWeapon** &weaponList, int &size, Point const &spaceShipPos);
        Saucer(Point newPos, int newSpeed, int newOrientation);
        ~Saucer();
        
        void render(SDL_Renderer* gRenderer, Point cameraPoint) override;
    private:
       int animation = 0;     
};


#endif