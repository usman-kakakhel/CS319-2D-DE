#ifndef __SAUCER_H
#define __SAUCER_H

#include "Enemy.h"
#include "FireRedBolt.h"

class Saucer : public Enemy{
    public:
        Saucer(Point newPos, int newSpeed, int newOrientation);
        ~Saucer() override;
        
        void render(Point cameraPoint) override;
        void updatePosition(Point spaceShipPos, Human* humanList, int size) override;
        void fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos) override;
	int getWidth() override;
	int getHeight() override;

    private:
       int animation = 0;
       
       //textures and image addresses
	   DisplayManager::CustomTexture* mCTexture = NULL;
       string saucerSprite = "../resources/saucer.png";
};


#endif
