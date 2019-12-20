#ifndef __SAUCERBLADES_H
#define __SAUCERBLADES_H

#include "Enemy.h"
#include "FireRedBolt.h"

class SaucerBlades : public Enemy{
    public:
        SaucerBlades(Point newPos, int newSpeed, int newOrientation);
        ~SaucerBlades() override;
        
        void render(Point cameraPoint) override;
        void updatePosition(Point spaceShipPos, Human* humanList, int size) override;
        void fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos) override;
	int getWidth() override;
	int getHeight() override; 
    private:
       int animation = 0;
       
       //textures and image addresses
	   DisplayManager::CustomTexture* mCTexture = NULL;
       string saucerSprite = "../resources/saucer_blades.png";
};


#endif
